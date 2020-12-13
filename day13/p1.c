/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 08:39:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/13 09:01:03 by mraasvel      ########   odam.nl         */
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
	size_t	time_id;
	size_t	original_id;
}				t_bus;

void	print_ids(t_bus *buses)
{
	for (size_t i = 0; i < BUS_COUNT; i++)
	{
		printf("%lu : ", buses[i].time_id);
		printf("%lu\n", buses[i].original_id);
	}
	
}

int	find_min(t_bus *buses)
{
	size_t	min;
	int		j;

	min = __INT_MAX__;
	for (size_t i = 0; i < BUS_COUNT; i++)
	{
		if (buses[i].time_id < min)
		{
			min = buses[i].time_id;
			j = i;
		}
	}
	return (j);
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
			j++;
		}
		i++;
	}
	ft_free_split(strings);
	return (0);
}

int		check_times(t_bus *buses)
{
	if (buses[0].time_id >= START_TIME &&
	buses[1].time_id >= START_TIME &&
	buses[2].time_id >= START_TIME &&
	buses[3].time_id >= START_TIME &&
	buses[4].time_id >= START_TIME &&
	buses[5].time_id >= START_TIME &&
	buses[6].time_id >= START_TIME &&
	buses[7].time_id >= START_TIME &&
	buses[8].time_id >= START_TIME)
		return (1);
	return (0);
}

size_t	get_timestamp(t_bus *buses)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (buses[0].time_id < START_TIME)
			buses[0].time_id += buses[0].original_id;
		if (buses[1].time_id < START_TIME)
			buses[1].time_id += buses[1].original_id;
		if (buses[2].time_id < START_TIME)
			buses[2].time_id += buses[2].original_id;
		if (buses[3].time_id < START_TIME)
			buses[3].time_id += buses[3].original_id;
		if (buses[4].time_id < START_TIME)
			buses[4].time_id += buses[4].original_id;
		if (buses[5].time_id < START_TIME)
			buses[5].time_id += buses[5].original_id;
		if (buses[6].time_id < START_TIME)
			buses[6].time_id += buses[6].original_id;
		if (buses[7].time_id < START_TIME)
			buses[7].time_id += buses[7].original_id;
		if (buses[8].time_id < START_TIME)
			buses[8].time_id += buses[8].original_id;
		if (check_times(buses) != 0)
			break ;
	}
	print_ids(buses);
	printf("\nmax: %lu\n", buses[find_min(buses)].time_id);
	printf("calculation: %lu\n", (buses[find_min(buses)].time_id - START_TIME) * buses[find_min(buses)].original_id);
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
		buses[i].time_id = 0;
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