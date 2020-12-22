/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 11:28:43 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 13:58:21 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day22.h"

int	*get_state(t_deck *deck);

int		check_states(t_list *states_1, t_deck *deck_1, t_list *states_2, t_deck *deck_2)
{
	t_deck	*finder_1;
	t_deck	*finder_2;
	int		i;
	int		j;

	while (states_1 != NULL)
	{
		finder_1 = deck_1;
		finder_2 = deck_2;
		i = 0;
		while (((int*)states_1->content)[i] != -1 && finder_1 != NULL)
		{
			if (finder_1->card != ((int*)states_1->content)[i])
				break ;
			i++;
			finder_1 = finder_1->next;
		}
		j = 0;
		while (((int*)states_2->content)[j] != -1 && finder_2 != NULL)
		{
			if (finder_2->card != ((int*)states_2->content)[j])
				break ;
			j++;
			finder_2 = finder_2->next;
		}
		if (((int*)states_1->content)[i] == -1 && ((int*)states_2->content)[j] == -1)
		{
			if (finder_1 == NULL && finder_2 == NULL)
				return (state_found);
		}
		states_1 = states_1->next;
		states_2 = states_2->next;
	}
	return (continue_game);
}

void	update_state(t_list **states, t_deck *deck)
{
	ft_lstadd_back(states, ft_lstnew(get_state(deck)));
}

void	destroy_state(t_list **states)
{
	ft_lstclear(states, free);
}

int	*get_state(t_deck *deck)
{
	int	*result;
	int	i;
	int	size;

	size = get_list_size(deck);
	result = malloc((size + 1) * sizeof(int));
	if (result == NULL)
		return (NULL);
	result[size] = -1;
	i = 0;
	while (deck != NULL)
	{
		result[i] = deck->card;
		deck = deck->next;
		i++;
	}
	return (result);
}
