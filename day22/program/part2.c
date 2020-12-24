/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   part2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 10:18:27 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 14:05:40 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day22.h"

int	play_game_p2(t_deck *p1, t_deck *p2, int game);

int	get_part2_result(t_deck *winner)
{
	int	size;
	int	total;

	size = get_list_size(winner);
	total = 0;
	while (winner != NULL)
	{
		total += size * winner->card;
		winner = winner->next;
		size--;
	}
	printf("Part 2 answer: %d\n", total);
	return (total);
}

int	play_game_p2(t_deck *p1, t_deck *p2, int game)
{
	t_list	*states_1;
	t_list	*states_2;
	int		round;
	int		size_p1;
	int		size_p2;
	int		result;

	size_p1 = get_list_size(p1);
	size_p2 = get_list_size(p2);
	states_1 = NULL;
	states_2 = NULL;
	round = 0;
	while (p1 != NULL && p2 != NULL)
	{
		size_p1--;
		size_p2--;
		if (check_states(states_1, p1, states_2, p2) == state_found)
		{
			result = win_p1;
			break ;
		}
		if (p1->card <= size_p1 && p2->card <= size_p2)
			result = play_game_p2(copy_n_elements(p1->next, p1->card), copy_n_elements(p2->next, p2->card), game + 1);
		else if (p1->card > p2->card)
			result = win_p1;
		else if (p2->card > p1->card)
			result = win_p2;
		update_state(&states_1, p1);
		update_state(&states_2, p2);
		if (result == win_p1)
		{
			append_element(&p1, p1->card);
			append_element(&p1, p2->card);
			size_p1 += 2;
		}
		else if (result == win_p2)
		{
			append_element(&p2, p2->card);
			append_element(&p2, p1->card);
			size_p2 += 2;
		}
		delete_element(&p1, p1->card);
		delete_element(&p2, p2->card);
		round++;
	}
	if (p1 == NULL)
		result = win_p2;
	else if (p2 == NULL)
		result = win_p1;
	if (game == 0)
	{
		print_list(p1);
		print_list(p2);
		if (result == win_p1)
		{
			printf("Player 1 won!\n");
			get_part2_result(p1);
		}
		else
		{
			printf("Player 2 won!\n");
			get_part2_result(p2);
		}
	}
	destroy_state(&states_1);
	destroy_state(&states_2);
	free_list(&p1);
	free_list(&p2);
	return (result);
}
