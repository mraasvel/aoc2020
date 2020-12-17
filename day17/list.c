/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 10:42:18 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/17 11:20:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "day17.h"

/*
** Takes one element from the hashtable and
** searches it for the key
** Returns ptr to list entry with key or
** Returns ptr to last list entry if not.
*/

LinkedList	*find_key_in_list(t_vector key, LinkedList *element)
{
	while (element->next != NULL)
	{
		if (hash_key_match(key, element->data.coord) == 0)
			break ;
		element = element->next;
	}
	return (element);
}

LinkedList	*create_new_entry(t_vector key)
{
	LinkedList	*new;

	new = (LinkedList*)malloc(1 * sizeof(LinkedList));
	if (new == NULL)
		return (NULL);
	new->data.coord.x = key.x;
	new->data.coord.y = key.y;
	new->data.coord.z = key.z;
	new->data.status = active;
	return (new);
}

void		free_linkedlist(LinkedList *start)
{
	LinkedList	*tmp;

	while (start != NULL)
	{
		tmp = start->next;
		free(start);
		start = tmp;
	}
}

void		delete_key_from_list(t_vector key, LinkedList *prev, LinkedList *start)
{
	while (start->next != NULL)
	{
		if (hash_key_match(start->data.coord, key) == 0)
			break ;
		start = start->next;
		prev = start;
	}
	if (hash_key_match(start->data.coord, key) == 0)
	{
		prev->next = start->next;
		free(start);
	}
}
