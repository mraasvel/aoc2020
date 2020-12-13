/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 10:27:13 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/13 11:35:53 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

typedef enum	e_dirs
{
	north,
	south,
	west,
	east
}				t_dirs;

typedef	struct	s_ship
{
	long long	north_south;
	long long	east_west;
	int			dir;
}				t_ship;

typedef struct	s_waypoint
{
	long long north_south;
	long long east_west;
}				t_waypoint;

static long long	ft_abs(long long a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	print_position(t_ship ship)
{
	printf("NS: %lld\n", ship.north_south);
	printf("EW: %lld\n", ship.east_west);
	if (ship.dir == north)
		printf("dir: north\n");
	else if (ship.dir == south)
		printf("dir: south\n");
	else if (ship.dir == west)
		printf("dir: west\n");
	else if (ship.dir == east)
		printf("dir: east\n");
	printf("Result: %lld\n", ft_abs(ship.north_south) + ft_abs(ship.east_west));
}

int	rotate_ship(char type, int degrees, t_ship *ship)
{
	if (degrees == 180)
	{
		if (ship->dir == north)
			ship->dir = south;
		else if (ship->dir == south)
			ship->dir = north;
		else if (ship->dir == east)
			ship->dir = west;
		else if (ship->dir == west)
			ship->dir = east;
	}
	else if (type == 'R')
	{
		if (degrees == 90)
		{
			if (ship->dir == north)
				ship->dir = east;
			else if (ship->dir == east)
				ship->dir = south;
			else if (ship->dir == south)
				ship->dir = west;
			else if (ship->dir == west)
				ship->dir = north;
		}
		else if (degrees == 270)
			rotate_ship('L', 90, ship);
	}
	else if (type == 'L')
	{
		if (degrees == 90)
		{
			if (ship->dir == north)
				ship->dir = west;
			else if (ship->dir == east)
				ship->dir = north;
			else if (ship->dir == south)
				ship->dir = east;
			else if (ship->dir == west)
				ship->dir = south;
		}
		else if (degrees == 270)
			rotate_ship('R', 90, ship);
	}
}

void rotate_waypoint(char type, int degrees, t_waypoint *waypoint)
{
	long long	tmp;

	if (degrees == 180)
	{
		waypoint->north_south = -1 * waypoint->north_south;
		waypoint->east_west = -1 * waypoint->east_west;
	}
	else if (type == 'R')
	{
		if (degrees == 270)
			rotate_waypoint('L', 90, waypoint);
		else
		{
			tmp = waypoint->north_south;
			waypoint->north_south = -waypoint->east_west;
			waypoint->east_west = tmp;
		}
	}
	else if (type == 'L')
	{
		if (degrees == 270)
			rotate_waypoint('R', 90, waypoint);
		else
		{
			tmp = waypoint->north_south;
			waypoint->north_south = waypoint->east_west;
			waypoint->east_west = -tmp;
		}
	}
}

int	process_instruction(char *line, t_ship *ship, t_waypoint *waypoint)
{
	int nbr;

	nbr = ft_atoi(line + 1);
	if (line[0] == 'F')
	{
		ship->north_south += nbr * waypoint->north_south;
		ship->east_west += nbr * waypoint->east_west;
	}
	else if (line[0] == 'N')
		waypoint->north_south += nbr;
	else if (line[0] == 'S')
		waypoint->north_south -= nbr;
	else if (line[0] == 'E')
		waypoint->east_west += nbr;
	else if (line[0] == 'W')
		waypoint->east_west -= nbr;
	else
		rotate_waypoint(line[0], nbr, waypoint);
	return (0);
}

int	read_in_file(char *pathname)
{
	int		fd;
	int		ret;
	t_ship	ship;
	t_waypoint waypoint;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = 1;
	ship.dir = east;
	ship.east_west = 0;
	ship.north_south = 0;
	waypoint.north_south = 1;
	waypoint.east_west = 10;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (*line != '\0')
			process_instruction(line, &ship, &waypoint);
		free(line);
	}
	print_position(ship);
	return (0);
}

int	main(void)
{
	// read_in_file("input.txt");
	read_in_file("test.txt");
	return (0);
}
