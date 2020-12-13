/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/09 11:19:00 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/09 15:00:38 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

uint64_t	check_if_valid(uint64_t *numbers, int index)
{
	uint64_t	nbr;
	int			i;
	int			j;
	int			k;

	nbr = numbers[index];
	i = 0;
	index--;
	while (i < 25)
	{
		j = index;
		k = 0;
		while (k < 25 - i)
		{
			if ((numbers[j] + numbers[index]) == nbr)
				return (1);
			j--;
			k++;
		}
		index--;
		i++;
	}
	return(-1);
}

int	find_first_problem(uint64_t *numbers)
{
	int	i;
	int	nbr;

	i = 25;
	nbr = -1;
	while (i < 1000)
	{
		if (check_if_valid(numbers, i) == -1)
			return (numbers[i]);
		i++;
	}
	return (nbr);
}

uint64_t	get_sum(uint64_t *numbers, int len)
{
	int	i;
	uint64_t	ret;

	i = 0;
	ret = 0;
	while (i < len)
	{
		ret += numbers[i];
		i++;
	}
	return (ret);
}

void	print_values(uint64_t *numbers, uint64_t sum, int len, int index)
{
	int	j;
	uint64_t	max;
	uint64_t	min;

	j = 0;
	max = 0;
	min = numbers[index];
	while (j < len)
	{
		if (j != 0)
			printf(" ");
		printf("%llu", numbers[j + index]);
		if (numbers[j + index] > max)
			max = numbers[j + index];
		if (numbers[j + index] < min)
			min = numbers[j + index];
		j++;
	}
	printf("\n");
	printf("max: %llu\nmin: %llu\nresult: %llu\n", max, min, max + min);
}

int	find_contiguous_set(uint64_t *numbers, uint64_t invalid)
{
	uint64_t	sum;
	int			len;
	int			i;

	len = 2;
	while (len < 1000)
	{
		sum = get_sum(numbers, len);
		i = 0;
		while (i < 1000 - len)
		{
			if (sum == invalid)
			{
				print_values(numbers, sum, len, i);
				return (0);
			}
			sum -= numbers[i];
			sum += numbers[i + len];
			i++;
		}
		len++;
	}
	return (-1);
}

int	read_in_file(char *pathname)
{
	int			ret;
	int			fd;
	uint64_t	numbers[1000];
	uint64_t	invalid;
	int			i;
	char		*line;

	ret = 1;
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("open error\n");
		return (-1);
	}
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			printf("gnl error\n");
			return (-1);
		}
		numbers[i] = ft_atoi(line);
		i++;
		free(line);
	}
	invalid = find_first_problem(numbers);
	printf("ret: %llu\n", invalid);
	find_contiguous_set(numbers, invalid);
	return (0);
}

int	main(void)
{
	read_in_file("input.txt");
	return (0);
}
