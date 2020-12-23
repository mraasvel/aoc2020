/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/23 08:32:58 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/23 09:55:31 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day23.h"


t_cups	*list_create(int value)
{
	t_cups	*new;

	new = (t_cups*)malloc(1 * sizeof(t_cups));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->cup = value;
	return (new);
}

void	list_append(t_cups **start, int value)
{
	t_cups	*finder;

	if (start == NULL)
		return ;
	if (*start == NULL)
	{
		*start = list_create(value);
		return ;
	}
	finder = *start;
	while (finder->next != NULL)
		finder = finder->next;
	finder->next = list_create(value);
}

void	list_delete(t_cups **start, int value)
{
	t_cups	*previous;
	t_cups	*current;

	if (start == NULL)
		return ;
	previous = NULL;
	current = *start;
	while (current != NULL)
	{
		if (current->cup == value)
		{
			if (previous == NULL)
				*start = (*start)->next;
			else
				previous->next = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

// extract n elements from list, going clockwise
t_cups	*list_extract(t_cups **start, t_cups *position, int n)
{
	int	i;
	int	start_found;
	t_cups	*new_start;
	t_cups	*current;

	current = position->next;
	start_found = 0;
	if (current == NULL)
	{
		current = *start;
		start_found = 1;
	}
	new_start = current;
	i = 1;
	while (i < n)
	{
		if (i < n && current->next == NULL)
		{
			current->next = *start;
			start_found = 1;
		}
		current = current->next;
		i++;
	}
	if (start_found == 1)
	{
		*start = current->next;
		position->next = NULL;
	}
	else
		position->next = current->next;
	current->next = NULL;
	return (new_start);
}

// put inserted list between position and position->next
// if position is the last element of the list, insert at start instead
void	list_insert(t_cups **start, t_cups *position, t_cups *inserted_list)
{
	t_cups	*finder;

	finder = inserted_list;
	while (finder->next != NULL)
		finder = finder->next;
	finder->next = position->next;
	position->next = inserted_list;
}

void	list_clear(t_cups **start)
{
	t_cups	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		free(*start);
		*start = tmp;
	}
}
