/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 09:53:17 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/17 11:24:17 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "day17.h"

void		hashtable_init(LinkedList *hashtable)
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable[i].next = NULL;
		hashtable[i].data.status = inactive;
		i++;
	}
}

/*
** some strange multiplications to "randomize" the hash index in order to decrease amount of hash collisions
** removed if statements for 0, because if statements are slower
** 0 0 1 and 1 0 0 will now result in different indexes etc
*/

size_t	hash(t_vector key)
{
	// if (key.x == 0)
	// 	key.x += 0x0FFFFFFF;
	// if (key.y == 0)
	// 	key.y += 0x00FFFFFF;
	// if (key.z == 0)
	// 	key.z += 0x000FFFFF;
	return ((size_t)(key.x * 0xfafdceb775 +  key.y * 0xd32a1752b8 + key.z * 0x51ff06ea0f) % TABLE_SIZE);
}

/*
** return 0 if vectors are identical
*/

int			hash_key_match(t_vector a, t_vector b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (0);
	return (1);
}

/*
** 1. get hash index
** 2. find out if key appears in index-list
** 3. add key if not, otherwise update value
*/

int			hash_insert(LinkedList *hashtable, t_vector key)
{
	size_t		index;
	LinkedList	*entry;

	index = hash(key);
	entry = find_key_in_list(key, hashtable + index);
	if (entry->data.status == inactive || hash_key_match(entry->data.coord, key) == 0)
	{
		entry->data.coord.x = key.x;
		entry->data.coord.y = key.y;
		entry->data.coord.z = key.z;
		entry->data.status = active;
	}
	else
	{
		entry->next = create_new_entry(key);
		if (entry->next == NULL)
			return (error);
	}
	return (success);
}

/*
** 1. get hash index
** 2. find out if key appears in index-list
** 3. set status to inactive, if it's part of the list we can delete the node from the list?
*/

void		hash_delete(LinkedList *hashtable, t_vector key)
{
	size_t		index;
	LinkedList	*entry;

	index = hash(key);
	if (hashtable[index].next == NULL)
		hashtable[index].data.status = inactive;
	else
		delete_key_from_list(key, hashtable + index, hashtable[index].next);
}

/*
** 1. find entry in hashtable using list and index
** 2. check if the key is actually there, else return inactive
** takes coordinate key as input and returns whether that coordinate has an active cube or not
*/

int			hash_fetch(LinkedList *hashtable, t_vector key)
{
	size_t		index;
	LinkedList	*entry;

	index = hash(key);
	entry = find_key_in_list(key, hashtable + index);
	if (hash_key_match(entry->data.coord, key) == 0)
		return (entry->data.status);
	else
		return (inactive);
}

void		hash_free(LinkedList *hashtable)
{
	size_t	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hashtable[i].next != NULL)
			free_linkedlist(hashtable[i].next);
		i++;
	}
}
