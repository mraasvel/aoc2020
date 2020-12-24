/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/24 08:31:19 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/24 12:40:23 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day24.h"

size_t	total_black_tiles = 0;
t_pair	min;
t_pair	max;

t_pair	gen_key(int x, int y)
{
	t_pair	new;

	new.x = x;
	new.y = y;
	return (new);
}

void	print_minmax(void)
{
	printf("Min: %d, %d\n", min.x, min.y);
	printf("Max: %d, %d\n", max.x, max.y);
}

int	p1_check_tile(t_pair key, LinkedList *hashtable)
{
	int	status;

	status = hash_get(key, hashtable);
	if (status == black)
		total_black_tiles--;
	else
		total_black_tiles++;
	if (hash_insert(key, hashtable) == error)
		return (error);
	return (success);
}

void	set_minmax(int x, int y)
{
	if (x < min.x)
		min.x = x;
	if (y < min.y)
		min.y = y;
	if (x > max.x)
		max.x = x;
	if (y > max.y)
		max.y = y;
}

// Coordinates = odd-r (odd row right)
// used https://www.redblobgames.com/grids/hexagons/ example
int	set_coordinate(char *line, LinkedList *hashtable)
{
	int x, y;
	int i;

	x = y = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'e')
			x++;
		else if (line[i] == 'w')
			x--;
		else if (line[i] == 's' || line[i] == 'n')
		{
			i++;
			if (line[i] == 'e' && y % 2 != 0)
				x++;
			else if (line[i] == 'w' && y % 2 == 0)
				x--;
			if (line[i - 1] == 's')
				y++;
			else
				y--;
		}
		i++;
	}
	if (p1_check_tile(gen_key(x, y), hashtable) == error)
		return (error);
	set_minmax(x, y);
	return (success);
}

int	read_data(int fd, LinkedList *hashtable)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (error);
		if (*line != '\0')
		{
			if (set_coordinate(line, hashtable) == error)
			{
				free(line);
				return (error);
			}
		}
		free(line);
	}
	return (success);
}

unsigned	adjacent_black_tiles_count(t_pair key, LinkedList *hashtable)
{
	unsigned	count;
	int			odd_even;

	count = 0;
	if (key.y % 2 == 0)
		odd_even = -1;
	else
		odd_even = 1;
	if (hash_get(gen_key(key.x + 1, key.y), hashtable) == black)
		count++;
	if (hash_get(gen_key(key.x - 1, key.y), hashtable) == black)
		count++;
	if (hash_get(gen_key(key.x, key.y + 1), hashtable) == black)
		count++;
	if (hash_get(gen_key(key.x, key.y - 1), hashtable) == black)
		count++;
	if (hash_get(gen_key(key.x + odd_even, key.y + 1), hashtable) == black)
		count++;
	if (hash_get(gen_key(key.x + odd_even, key.y - 1), hashtable) == black)
		count++;
	return (count);
}

// Check if current coordinate should be switched to black or not
// if it's black and switches to white, don't add it to the new hashtable
int	check_adjacents(t_pair key, LinkedList *hashtable)
{
	int			status;
	unsigned	count;

	status = hash_get(key, hashtable);
	count = adjacent_black_tiles_count(key, hashtable);
	if (status == black && (count == 1 || count == 2))
		return (black);
	if (status == white && count == 2)
	{
		total_black_tiles += 1;
		return (black);
	}
	if (status == black)
	{
		total_black_tiles -= 1;
	}
	return (white);
}

int	get_new_day(LinkedList *hashtable, LinkedList *new_hashtable)
{
	t_pair	key;

	for (int y = min.y - 1; y <= max.y + 1; y++)
	{
		for (int x = min.x - 1; x <= max.x + 1; x++)
		{
			key.x = x;
			key.y = y;
			if (check_adjacents(key, hashtable) == black)
			{
				if (hash_insert(key, new_hashtable) == error)
					return (error);
			}
		}
	}
	return (success);
}

// switch each day between two hashtables
// min and max are used to check, so a lot of redundant checks are done as well
int	p2_cycle_days(LinkedList **hashtable)
{
	LinkedList	*new_hashtable;
	size_t		i;
	t_pair		check_these;

	i = 0;
	while (i < DAYS)
	{
		new_hashtable = (LinkedList*)malloc(TABLE_SIZE * sizeof(LinkedList));
		if (new_hashtable == NULL)
			return (error);
		hashtable_init(new_hashtable);
		if (get_new_day(*hashtable, new_hashtable) == error)
		{
			hashtable_free(new_hashtable);
			return (error);
		}
		hashtable_free(*hashtable);
		*hashtable = new_hashtable;
		min.x -= 1;
		min.y -= 1;
		max.x += 1;
		max.y += 1;
		i++;
	}
	printf("Part 2: (day %lu): %lu\n", i, total_black_tiles);
	return (success);
}

/* #define PATH for input in day24.h */
int	main(void)
{
	LinkedList	*hashtable;
	int			fd;

	min.x = INT_MAX;
	min.y = INT_MAX;
	max.x = 0;
	max.y = 0;
	fd = open(PATH, O_RDONLY);
	if (fd == -1)
	{
		perror("Open");
		return (0);
	}
	hashtable = (LinkedList*)malloc(TABLE_SIZE * sizeof(LinkedList));
	if (hashtable == NULL)
		return (0);
	hashtable_init(hashtable);
	if (read_data(fd, hashtable) == error)
	{
		printf("Error in part 1\n");
		hashtable_free(hashtable);
		return (0);
	}
	printf("Part 1 (day 0): %lu\n", total_black_tiles);
	p2_cycle_days(&hashtable);
	hashtable_free(hashtable);
	return (0);
}
