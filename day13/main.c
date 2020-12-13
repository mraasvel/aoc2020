/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 08:39:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/13 10:08:42 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

#define START_TIME 1000510
#define BUS_COUNT 9

typedef struct	s_bus
{
	size_t	original_id;
	size_t	value;
	int		timestamp;
}				t_bus;

void	print_ids(t_bus *buses)
{
	for (size_t i = 0; i < BUS_COUNT; i++)
	{
		printf("%lu : %d : %lu\n", buses[i].value, buses[i].timestamp, buses[i].original_id);
	}
	
}

int	fill_buses(t_bus *buses, char *line)
{
	char	**strings;
	size_t	i;
	size_t	j;

	strings = ft_split(line, ',');
	if (strings == NULL)
		return (-1);
	i = j = 0;
	while (strings[i] != NULL)
	{
		if (strings[i][0] != 'x')
		{
			buses[j].original_id = ft_atoi(strings[i]);
			buses[j].timestamp = i;
			j++;
		}
		i++;
	}
	ft_free_split(strings);
	return (0);
}

int		check_timestamp(t_bus *buses)
{
	size_t	i;

	i = 0;
	while (i < 9)
	{
		if (buses[i].value - buses[0].value > buses[i].timestamp)
			return (0);
		if (buses[i].value - buses[0].value != buses[i].timestamp)
			return (0);
		i++;
	}
}

int	set_timestamp(t_bus *buses, int i)
{
	if (i == 8)
		print_ids(buses);
	while (buses[i].value <= buses[i - 1].value)
		buses[i].value += buses[i].original_id;
	if (i == 8 && buses[i].value - buses[0].value == buses[i].timestamp)
		return (0);
	if (buses[i].value - buses[0].value == buses[i].timestamp)
		return (set_timestamp(buses, i + 1));
	return (1);
}

size_t	get_timestamp(t_bus *buses)
{
	int	ret;

	print_ids(buses);
	while (1)
	{
		ret = set_timestamp(buses, 1);
		if (ret == 0)
			break ;
		// if (buses[1].value - buses[0].value == buses[1].timestamp)
		// 	printf("%lu\n", buses[1].value - buses[0].value);
		buses[0].value += buses[0].original_id;
	}
	print_ids(buses);
	return (0);
}

int	read_in_file(char *pathname)
{
	t_bus	buses[BUS_COUNT];
	char	*line;
	char	**strings;
	int		fd;
	int		ret;

	for (size_t i = 0; i < BUS_COUNT; i++)
	{
		buses[i].value = 0;
	}
	fd= open(pathname, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = ft_getline(fd, &line);
	if (ret == -1)
		return (-1);
	ret = fill_buses(buses, line);
	free(line);
	if (ret == -1)
		return (-1);
	get_timestamp(buses);
	return (0);
}

int	main(void)
{
	read_in_file("input.txt");
	// read_in_file("test.txt");
	return	(0);
}