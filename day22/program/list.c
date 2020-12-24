/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 08:30:26 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 10:35:44 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day22.h"

// create, append, delete

t_deck	*create_element(int value)
{
	t_deck	*new;

	new = (t_deck*)malloc(1 * sizeof(t_deck));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->card = value;
	return (new);
}

int		append_element(t_deck **start, int value)
{
	t_deck	*find_last;

	if (start == NULL)
		return (-1);
	if (*start == NULL)
	{
		*start = create_element(value);
		if (start == NULL)
			return (-1);
		return (0);
	}
	find_last = *start;
	while (find_last->next != NULL)
		find_last = find_last->next;
	find_last->next = create_element(value);
	if (find_last->next == NULL)
		return (-1);
	return (0);
}

void	delete_element(t_deck **start, int value)
{
	t_deck	*previous;
	t_deck	*current;

	current = *start;
	previous = NULL;
	while (current != NULL)
	{
		if (current->card == value)
		{
			if (previous == NULL)
				*start = current->next;
			else
				previous->next = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	free_list(t_deck **start)
{
	t_deck	*tmp;

	if (start == NULL)
		return ;
	while (*start != NULL)
	{
		tmp = (*start)->next;
		free(*start);
		*start = tmp;
	}
}

int		get_list_size(t_deck *start)
{
	int	cnt;

	cnt = 0;
	while (start != NULL)
	{
		start = start->next;
		cnt++;
	}
	return (cnt);
}

t_deck	*copy_deck(t_deck *start)
{
	t_deck	*new_list;

	new_list = NULL;
	while (start != NULL)
	{
		append_element(&new_list, start->card);
		start = start->next;
	}
	return (new_list);
}

t_deck	*copy_n_elements(t_deck *start, int n)
{
	t_deck	*new_list;

	new_list = NULL;
	while (start != NULL && n > 0)
	{
		append_element(&new_list, start->card);
		start = start->next;
		n--;
	}
	return (new_list);
}

int	compare_decks(t_deck *p1, t_deck *p2)
{
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->card != p2->card)
			return (1);
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 == NULL && p2 == NULL)
		return (0);
	return (1);
}
