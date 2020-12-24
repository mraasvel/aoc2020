/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/24 09:28:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/24 10:18:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day24.h"

int		hash_key_match(t_pair a, t_pair b)
{
	if (a.x == b.x && a.y == b.y)
		return (0);
	return (1);
}

size_t	hash(t_pair key)
{
	return ((size_t)(key.x * 0xfafdceb775 ^ key.y * 0xd32a1752b8) % TABLE_SIZE);
}

void	hashtable_init(LinkedList *hashtable)
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable[i].next = NULL;
		hashtable[i].data.status = white;
		hashtable[i].data.key.x = 0;
		hashtable[i].data.key.y = 0;
		i++;
	}
}

void	hashtable_free(LinkedList *hashtable)
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hashtable[i].next != NULL)
			list_free(hashtable[i].next);
		i++;
	}
	free(hashtable);
}

int		hash_get(t_pair key, LinkedList *hashtable)
{
	LinkedList	*match;

	match = find_key(hashtable + hash(key), key);
	if (match == NULL)
		return (white);
	return (match->data.status);
}

int		hash_insert(t_pair key, LinkedList *hashtable)
{
	size_t		index;
	LinkedList	*match;

	index = hash(key);
	match = find_key(hashtable + index, key);
	if (match == NULL)
	{
		if (list_add_front(hashtable + index, key) == error)
		{
			return (error);
		}
	}
	else
	{
		if (match->data.status == white)
			match->data.status = black;
		else
			match->data.status = white;
	}
	return (success);
}
