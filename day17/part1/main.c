/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 08:23:59 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/17 13:29:00 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "day17.h"
#include "libft.h"

size_t	active_count = 0;

void		set_minmax(t_vector *max, t_vector *min)
{
	min->x = 0x7FFFFFFF;
	min->y = 0x7FFFFFFF;
	min->z = 0x7FFFFFFF;
	max->x = 0;
	max->y = 0;
	max->z = 0;
}

t_vector	get_vector(int x, int y, int z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vector	vector_add(t_vector vector, int v)
{
	vector.x += v;
	vector.y += v;
	vector.z += v;
	return (vector);
}

void	print_hash(t_vector vector)
{
	size_t	i;

	i = hash(vector);
	printf("%02d %02d %02d : |%lu|\n", vector.x, vector.y, vector.z, i);
}

void	print_vector(t_vector vector)
{
	printf("v: %d %d %d\n", vector.x, vector.y, vector.z);
}

void	print_minmax(t_vector max, t_vector min)
{
	printf("max: %d %d %d\n", max.x, max.y, max.z);
	printf("min: %d %d %d\n", min.x, min.y, min.z);
}

int	get_initial_values(char *pathname, LinkedList *hashtable, t_vector *max, t_vector *min)
{
	int		fd;
	int		ret;
	int		x;
	int		y;
	char	*line;
	
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (error);
	ret = 1;
	y = 0;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (error);
		x = 0;
		while (line[x] != '\0')
		{
			if (line[x] == '#')
			{
				max->x = ft_max(x, max->x);
				max->y = ft_max(y, max->y);
				max->z = ft_max(0, max->z);
				min->x = ft_min(x, min->x);
				min->y = ft_min(y, min->y);
				min->z = ft_min(0, min->z);
				active_count += 1;
				hash_insert(hashtable, get_vector(x, y, 0));
				printf("insert: ");
				print_vector(get_vector(x, y, 0));
			}
			x++;
		}
		free(line);
		y++;
	}
	return (success);
}

int	check_adjacent_cubes(t_vector key, LinkedList *hashtable, t_vector max, t_vector min)
{
	int	active_adjacent_count;

	active_adjacent_count = 0;
	for (int i = key.x - 1; i <= key.x + 1; i++)
	{
		for (int j = key.y - 1; j <= key.y + 1; j++)
		{
			for (int k = key.z - 1; k <= key.z + 1; k++)
			{
				if (hash_fetch(hashtable, get_vector(i, j, k)) == active)
				{
					if (hash_key_match(key, get_vector(i, j, k)) != 0)
					{
						active_adjacent_count += 1;
						if (active_adjacent_count > 3)
							return (active_adjacent_count);
					}
				}
			}
		}
	}
	return (active_adjacent_count);
}

void	print_current_state(LinkedList *hashtable, t_vector max, t_vector min)
{
	t_vector	key;

	for (int z = min.z + 1; z <= max.z - 1; z++)
	{
		printf("z = %d\n", z);
		for (int y = min.y + 1; y <= max.y - 1; y++)
		{
			for (int x = min.x + 1; x <= max.x - 1; x++)
			{
				key = get_vector(x, y, z);
				if (hash_fetch(hashtable, key) == active)
					printf("#");
				else
					printf(".");
			}
			printf("\n");
		}
		printf("\n");
	}
}

int	cycle_through(LinkedList **hashtable, t_vector max, t_vector min)
{
	int			cycles;
	int			adj;
	t_vector	key;

	cycles = 0;
	max = vector_add(max, 1);
	min = vector_add(min, -1);
	while (cycles < 6)
	{
		// printf("Cycle: %d\n", cycles);
		// print_current_state(hashtable[cycles], max, min);
		for (int z = min.z; z <= max.z; z++)
		{
			for (int y = min.y; y <= max.y; y++)
			{
				for (int x = min.x; x <= max.x; x++)
				{
					key = get_vector(x, y, z);
					if (hash_fetch(hashtable[cycles], key) == active)
					{
						adj = check_adjacent_cubes(key, hashtable[cycles], max, min);
						if (adj == 2 || adj == 3)
							hash_insert(hashtable[cycles + 1], key);
						else
							active_count -= 1;
					}
					else
					{
						adj = check_adjacent_cubes(key, hashtable[cycles], max, min);
						if (adj == 3)
						{
							hash_insert(hashtable[cycles + 1], key);
							active_count += 1;
						}
					}
				}
			}
		}
		max = vector_add(max, 1);
		min = vector_add(min, -1);
		cycles++;
	}
}

/*
** all active squares are stored in a hashtable
** instead of a map like map[x][y][z] the table takes a key_vector(x, y, z)
*/

int	main(void)
{
	// LinkedList	hashtable[7][TABLE_SIZE];
	LinkedList	**hashtable;
	t_vector	max;
	t_vector	min;

	hashtable = (LinkedList**)malloc(7 * sizeof(LinkedList*));
	for (size_t i = 0; i < 7; i++)
	{
		hashtable[i] = (LinkedList*)malloc(TABLE_SIZE * sizeof(LinkedList));
		hashtable_init(hashtable[i]);
	}
	set_minmax(&max, &min);
	get_initial_values("input.txt", hashtable[0], &max, &min);
	cycle_through(hashtable, max, min);
	for (size_t i = 0; i < 7; i++)
	{
		hash_free(hashtable[i]);
		free(hashtable[i]);
	}
	free(hashtable);
	printf("cube count: %lu\n", active_count);
	return (0);
}
