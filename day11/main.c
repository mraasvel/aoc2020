/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 08:29:30 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/11 13:09:20 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define LINE_SIZE 92
#define LINES 99

typedef enum	e_nums
{
	floor,
	empty,
	taken,
	no_change,
	change
}				t_nums;

typedef struct	s_spot
{
	int	seat;
}				t_spot;

void	*ft_free_map(t_spot **map)
{
	int	i;

	i = 0;
	while (i < LINES)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (NULL);
}

void	*ft_error_map(t_spot **map, int i)
{
	while (i > 0)
	{
		i--;
		free(map[i]);
	}
	free(map);
	return (NULL);
}

void	ft_fill_line(t_spot *map, char *line)
{
	int	x;

	x = 0;
	while (x < LINE_SIZE)
	{
		if (line[x] == '.')
			map[x].seat = floor;
		else if (line[x] == 'L')
			map[x].seat = empty;
		else if (line[x] == '#')
			map[x].seat = taken;
		x++;
	}
}

t_spot	**read_in_file(char *pathname)
{
	int		fd;
	int		ret;
	char	*line;
	t_spot	**map;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = 1;
	map = (t_spot**)malloc(LINES * sizeof(t_spot*));
	if (map == NULL)
		return (NULL);
	for (int j = 0; j < LINES; j++)
	{
		map[j] = (t_spot*)malloc(LINE_SIZE * sizeof(t_spot));
		if (map[j] == NULL)
		{
			ft_error_map(map, j);
			return (NULL);
		}
	}
	int	y;
	y = 0;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
		{
			ft_free_map(map);
			return (NULL);
		}
		ft_fill_line(map[y], line);
		y++;
		free(line);
	}
	return (map);
}

t_spot	**malloc_map(void)
{
	t_spot	**map;

	map = (t_spot**)malloc(LINES * sizeof(t_spot*));
	if (map == NULL)
		return (NULL);
	for (size_t i = 0; i < LINES; i++)
	{
		map[i] = (t_spot*)malloc(LINE_SIZE * sizeof(t_spot));
		if (map[i] == NULL)
		{
			ft_error_map(map, i);
			return (NULL);
		}
	}
	
	return (map);
}

void	print_map(t_spot **map)
{
	for (size_t y = 0; y < LINES; y++)
	{
		for (size_t x = 0; x < LINE_SIZE; x++)
		{
			if (map[y][x].seat == floor)
				printf(".");
			else if (map[y][x].seat == empty)
				printf("L");
			else if (map[y][x].seat == taken)
				printf("#");
		}
		printf("\n");
	}
}

int		get_top(t_spot **map, size_t x, size_t y)
{
	int	cnt;
	int	i;
	int	j;

	if (y == 0)
		return (0);
	cnt = 0;
	y -= 1;
	if (x != 0)
	{
		i = x - 1;
		j = y;
		while (i > 0 && j > 0 && map[j][i].seat == floor)
		{
			i--;
			j--;
		}
		if (map[j][i].seat == taken)
			cnt++;
	}
	i = x;
	j = y;
	while (j > 0 && map[j][i].seat == floor)
	{
		j--;
	}
	if (map[j][i].seat == taken)
		cnt++;
	if (x != LINE_SIZE - 1)
	{
		i = x + 1;
		j = y;
		while (i < LINE_SIZE - 1 && j > 0 && map[j][i].seat == floor)
		{
			i++;
			j--;
		}
		if (map[j][i].seat == taken)
			cnt++;
	}
	return (cnt);
}

int		get_sides(t_spot **map, size_t x, size_t y)
{
	int	cnt;
	int	i;

	cnt = 0;
	if (x != 0)
	{
		i = x - 1;
		while (i > 0 && map[y][i].seat == floor)
			i--;
		if (map[y][i].seat == taken)
			cnt++;
	}
	if (x != LINE_SIZE - 1)
	{
		i = x + 1;
		while (i < LINE_SIZE - 1 && map[y][i].seat == floor)
			i++;
		if (map[y][i].seat == taken)
			cnt++;
	}
	return (cnt);
}

int		get_bottom(t_spot **map, size_t x, size_t y)
{
	int	cnt;
	int	t_x, t_y;

	if (y == LINES - 1)
		return (0);
	cnt = 0;
	if (x != 0)
	{
		t_x = x - 1;
		t_y = y + 1;
		while (t_x > 0 && t_y < LINES - 1 && map[t_y][t_x].seat == floor)
		{
			t_x--;
			t_y++;
		}
		if (map[t_y][t_x].seat == taken)
			cnt++;
	}
	t_y = y + 1;
	while (t_y < LINES - 1 && map[t_y][x].seat == floor)
		t_y++;
	if (map[t_y][x].seat == taken)
		cnt++;
	if (x != LINE_SIZE - 1)
	{
		t_y = y + 1;
		t_x = x + 1;
		while (t_x < LINE_SIZE - 1 && t_y < LINES - 1 && map[t_y][t_x].seat == floor)
		{
			t_x++;
			t_y++;
		}
		if (map[t_y][t_x].seat == taken)
			cnt++;
	}
	return (cnt);
}

// first we only check the adjacent seats.
// if no adjacent seats are taken: return taken
// else if at least 4 adjacent seats are taken, return empty
int		get_new_seat_value(t_spot **map, size_t x, size_t y)
{
	int	occupied_count;

	occupied_count = 0;
	occupied_count += get_top(map, x, y);
	occupied_count += get_sides(map, x, y);
	if (occupied_count >= 5)
		return (empty);
	occupied_count += get_bottom(map, x, y);
	if (occupied_count >= 5)
		return (empty);
	else if (occupied_count == 0)
		return (taken);
	else
		return (map[y][x].seat);
}

int	create_new_map(t_spot ***map, t_spot ***tmp_map)
{
	t_spot	**swapper;
	size_t	x, y;
	int	change_bool;

	change_bool = no_change;
	y = 0;
	while (y < LINES)
	{
		x = 0;
		while (x < LINE_SIZE)
		{
			if ((*map)[y][x].seat == floor)
				(*tmp_map)[y][x].seat = floor;
			else
				(*tmp_map)[y][x].seat = get_new_seat_value(*map, x, y);
			if ((*tmp_map)[y][x].seat != (*map)[y][x].seat)
				change_bool = change;
			x++;
		}
		y++;
	}
	swapper = *map;
	*map = *tmp_map;
	*tmp_map = swapper;
	return (change_bool);
}

void	print_occupied_seats(t_spot **map)
{
	int	cnt;

	cnt = 0;
	for (int y = 0; y < LINES; y++)
	{
		for (int x = 0; x < LINE_SIZE; x++)
		{
			if (map[y][x].seat == taken)
				cnt++;
		}
	}
	printf("Occupied seat count: %d\n", cnt);
}

int	main(void)
{
	t_spot	**map;
	t_spot	**tmp_map;

	map = read_in_file("input.txt");
	if (map == NULL)
		return (0);
	tmp_map = malloc_map();
	if (tmp_map == NULL)
	{
		ft_free_map(map);
		return (0);
	}
	int	changed;
	changed = change;
	while (changed != no_change)
	{
		changed = create_new_map(&map, &tmp_map);
	}
	print_occupied_seats(map);
	print_occupied_seats(tmp_map);
	ft_free_map(map);
	ft_free_map(tmp_map);
	return (0);
}
