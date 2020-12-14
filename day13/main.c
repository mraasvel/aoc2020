/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/13 08:39:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/14 09:26:25 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

#define START_TIME 1000510
#define BUS_COUNT 3

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

int	testing(t_bus *buses)
{
	size_t	m;
	size_t	m2;
	size_t	incrementor;

	m = 0;
	int	i = 0;
	incrementor = buses[0].original_id * buses[1].original_id;
	while (i < incrementor)
	{
		if (m % buses[0].original_id == buses[0].timestamp && m % buses[1].original_id == buses[1].timestamp){
			printf("%ld\n", m);
			break ;
		}
		m++;
		i++;
	}
	printf("m1: %ld\n", m);
	printf("%ld - %ld - %ld\n", m % 17, m % 13, incrementor);
	printf("\n");
	m2 = 0;
	while (1)
	{
		if (m2 % buses[0].original_id == buses[0].timestamp && m2 % buses[2].original_id == buses[2].timestamp)
			break ;
		m2++;
	}
	printf("m2: %ld\n", m2);
	printf("%ld %ld\n", 3417 % (buses[0].original_id * buses[2].original_id), 3417 % m2);
	// printf("")
	return (0);
}

static unsigned long long	find_nbr(t_bus *buses)
{
	size_t	m;
	size_t	i;
	size_t	nbr = 0;
	size_t	product = 1;

	i = 0;
	while (i < BUS_COUNT)
	{
		m = 0;
		while (m < buses[i].original_id)
		{
			if (!(((m * product + nbr) + buses[i].timestamp) % buses[i].original_id))
			{
				nbr = m * product + nbr;
				product *= buses[i].original_id;
				printf("%lu divided by %ld gives remainder %d\n", nbr, buses[i].original_id, buses[i].timestamp);
				break ;
			}
			m++;
		}
		i++;
	}
	printf("nbr: %ld\n", nbr);
	return (nbr);
}

// static unsigned long long	find_nbr(t_bus *buses)
// {
// 	int m;
// 	int	i;
// 	int	table[100];
// 	unsigned long long nbr = 0;
// 	unsigned long long product = 1;

// 	str = ft_strchr(str, 10) + 1;
// 	printf("%s\n", str);
// 	i = 0;
// 	while (*str)
// 	{
// 		if (ft_isdigit(*str))
// 		{
// 			table[i] = ft_atoi(str);
// 			str += ft_numlen(table[i]) + 1;
// 			m = 0;
// 			while (m < table[i])
// 			{
// 				if (!(((m * product + nbr) + i) % table[i]))
// 				{
// 					nbr = m * product + nbr;
// 					product *= table[i];
// 					printf("%llu divided by %d gives remainder %d\n", nbr, table[i], i);
// 					break ;
// 				}
// 				m++;
// 			}
// 		}
// 		else if (*str == 'x')
// 			str += 2;
// 		i++;
// 	}
// 	return
// }

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
	find_nbr(buses);
	return (0);
}

int	main(void)
{
	// read_in_file("input.txt");
	read_in_file("test.txt");
	return	(0);
}