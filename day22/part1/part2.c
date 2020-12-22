/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   part2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 10:18:27 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 10:56:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day22.h"

// size_p1 and size_p2 will include the cards drawn for current round.
int	play_round(t_deck **p1, t_deck **p2, int size_p1, int size_p2)
{
	
}

// send copies of initial_p1 and initial_p2
int	check_previous_states(t_deck *initial_p1, t_deck *initial_p2, t_deck *current_p1, t_deck *current_p2, int round)
{
	int	i;

	i = 0;
	while (i < round)
	{
		if (compare_decks(initial_p1, current_p1) == 0 && compare_decks(initial_p2, current_p2) == 0)
			break ;
		play_round(&initial_p1, &initial_p2, get_list_size(initial_p1), get_list_size(initial_p2));
		i++;
	}
	free_list(&initial_p1);
	free_list(&initial_p2);
	if (i == round)
		return (continue_game);
	return (state_found);
}

int	recursive_combat(t_deck *p1, t_deck *p2, int size_p1, int size_p2)
{
	free_list(&p1);
	free_list(&p2);
}

int	play_game_p2(t_deck *p1, t_deck *p2, int game)
{
	t_deck	*initial_p1;
	t_deck	*initial_p2;
	int		round;
	int		size_p1;
	int		size_p2;
	int		result;

	initial_p1 = copy_deck(p1);
	initial_p2 = copy_deck(p2);
	size_p1 = get_list_size(p1);
	size_p2 = get_list_size(p2);
	round = 0;
	// printf("Round %d (game %d)\n", round + 1, game + 1);
	// print_list(p1);
	// print_list(p2);
	while (p1 != NULL && p2 != NULL)
	{
		size_p1--;
		size_p2--;
		if (check_previous_states(copy_deck(initial_p1), copy_deck(initial_p2), p1, p2, round) == state_found)
		{
			result = win_p1;
			break ;
		}
		if (p1->card <= size_p1 && p2->card <= size_p2)
		{
			// print_list(p1);
			// print_list(p2);
			result = play_game_p2(copy_n_elements(p1->next, p1->card), copy_n_elements(p2->next, p2->card), game + 1);
			// if (result == win_p1)
				// printf("Player 1 won game %d\n\n", game + 1);
			// else
				// printf("Player 2 won game %d\n\n", game + 1);
			// result = recursive_combat(copy_n_elements(p1->next, p1->card), copy_n_elements(p2->next, p2->card), p1->card, p2->card);
		}
		else if (p1->card > p2->card)
			result = win_p1;
		else if (p2->card > p1->card)
			result = win_p2;
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
		// printf("Round %d (game %d)\n", round + 1, game + 1);
		// print_list(p1);
		// print_list(p2);
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
			get_part1_result(p1);
		else
			get_part1_result(p2);
	}
	free_list(&initial_p1);
	free_list(&initial_p2);
	free_list(&p1);
	free_list(&p2);
	return (result);
}
