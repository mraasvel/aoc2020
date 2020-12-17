/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 08:23:59 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/17 11:25:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "day17.h"
#include "libft.h"


t_vector	get_vector(int x, int y, int z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

void	print_hash(t_vector vector)
{
	size_t	i;

	i = hash(vector);
	printf("%02d %02d %02d : |%lu|\n", vector.x, vector.y, vector.z, i);
}

int	main(void)
{
	LinkedList	hashtable[TABLE_SIZE];

	hashtable_init(hashtable);
	hash_insert(hashtable, get_vector(1, 0, 0));
	hash_delete(hashtable, get_vector(1, 0, 0));
	hash_insert(hashtable, get_vector(0, 1, 0));
	printf("%d %d\n", hash_fetch(hashtable, get_vector(1, 0, 0)), active);
	hash_free(hashtable);
	return (0);
}
