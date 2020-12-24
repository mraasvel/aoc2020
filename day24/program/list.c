/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/24 09:33:59 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/24 09:50:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day24.h"

// first time tile is identified, it's flipped to black
LinkedList	*list_create(t_pair key)
{
	LinkedList	*new;

	new = (LinkedList*)malloc(1 * sizeof(LinkedList));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->data.key.x = key.x;
	new->data.key.y = key.y;
	new->data.status = black;
	return (new);
}

int			list_add_front(LinkedList *hashtable, t_pair key)
{
	LinkedList	*tmp;

	tmp = hashtable->next;
	hashtable->next = list_create(key);
	if (hashtable->next == NULL)
	{
		hashtable->next = tmp;
		return (error);
	}
	hashtable->next->next = tmp;
	return (success);
}

LinkedList	*find_key(LinkedList *hashtable, t_pair key)
{
	while (hashtable != NULL)
	{
		if (hash_key_match(hashtable->data.key, key) == 0)
			return (hashtable);
		hashtable = hashtable->next;
	}
	return (NULL);
}

LinkedList	*list_free(LinkedList *hashtable)
{
	LinkedList	*tmp;

	while (hashtable != NULL)
	{
		tmp = hashtable->next;
		free(hashtable);
		hashtable = tmp;
	}
}
