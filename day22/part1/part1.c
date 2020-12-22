/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   part1.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 10:17:40 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 10:17:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day22.h"

int	get_part1_result(t_deck *winner)
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
	printf("Part 1 answer: %d\n", total);
	return (total);
}

int	play_game_p1(t_deck *p1, t_deck *p2)
{
	int	tmp;
	int	tmp2;

	while (p1 != NULL && p2 != NULL)
	{
		tmp = (p1)->card;
		tmp2 = (p2)->card;
		if (tmp > tmp2)
		{
			delete_element(&p1, tmp);
			delete_element(&p2, tmp2);
			append_element(&p1, tmp);
			append_element(&p1, tmp2);
		}
		else
		{
			delete_element(&p2, tmp2);
			delete_element(&p1, tmp);
			append_element(&p2, tmp2);
			append_element(&p2, tmp);
		}
	}
	printf("\nPart 1:\nPlayer 1: ");
	print_list(p1);
	printf("Player 2: ");
	print_list(p2);
	if (p1 == NULL)
	{
		printf("player 2 wins!\n");
		get_part1_result(p2);
	}
	else
	{
		printf("player 1 wins!\n");
		get_part1_result(p1);
	}
	printf("\n");
	free_list(&p1);
	free_list(&p2);
	return (0);
}
