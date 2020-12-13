/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/10 11:05:02 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/10 14:42:26 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

typedef enum	e_errnum
{
	error = -1,
	success,
	open_error,
	malloc_error,
	gnl_error
}				t_errnum;

void	ft_perror(t_errnum errnum)
{
	static const char	*errors[] = {
		"success",
		"open_error",
		"malloc_error",
		"gnl_error",
	};

	ft_putstr_fd((char*)(errors[errnum]), 2);
	ft_putchar_fd('\n', 2);
}

void	swap_ints(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_int_table(int *table, size_t size)
{
	int	key;
	int	i;
	int	j;

	i = 1;
	while (i < size)
	{
		j = i - 1;
		key = table[i];
		while (j >= 0)
		{
			if (table[j] > key)
				table[j + 1] = table[j];
			else
				break ;
			j--;
		}
		table[j + 1] = key;
		i++;
	}
}

void	print_int_table(int *table, size_t size)
{
	int	cnt;

	cnt = 1;
	while (size-- > 0)
	{
		// ft_putll(cnt, 0);
		// ft_putstr(": ");
		ft_putll(*table, 0);
		ft_putchar_fd('\n', 1);
		table++;
		cnt++;
	}
}

int	get_differences(int *table, size_t size)
{
	size_t	i;
	int	count1;
	int	count3;
	int	difference;

	i = 0;
	count1 = count3 = 0;
	printf("c1: %d\nc3: %d\n", count1, count3);
	while (i < size - 1)
	{
		difference = table[i + 1] - table[i];
		if (difference > 3 || difference < 1)
			return (error);
		if (difference == 3)
			count3++;
		else if (difference == 1)
			count1++;
		else if (difference == 2)
			printf("2 difference\n");
		i++;
	}
	printf("c1: %d\nc3: %d\n", count1, count3);
	return ((count1) * (count3));
}

void print_size_t_table(unsigned long long *routes, int size)
{
	while (size > 0)
	{
		printf("%llu\n", *routes);
		routes++;
		size--;
	}
}

void	set_options(unsigned long long *routes, int i, int size, int *table)
{
	int	difference;

	routes[i] = routes[i + 1];
	difference = table[i + 2] - table[i];
	if (difference == 2 || difference == 3)
	{
		routes[i] += routes[i + 2];
		if (difference == 3)
			return ;
	}
	if (i == size - 3)
		return ;
	difference = table[i + 3] - table[i];
	if (difference == 3)
		routes[i] += routes[i + 3];
}

int	get_routes(int *table, int size)
{
	unsigned long long	*routes;
	int					i;

	routes = (unsigned long long*)malloc(size * sizeof(unsigned long long));
	if (routes == NULL)
		return (malloc_error);
	routes[size - 1] = 0;
	routes[size - 2] = 1;
	i = size - 3;
	while (i >= 0)
	{
		set_options(routes, i, size, table);
		i--;
	}
	printf("routes: %llu\n", routes[0]);
	free(routes);
	return (success);
}

int	read_in_data(char *pathname)
{
	char	*line;
	int		fd;
	int		ret;
	int		*jolts;
	int		size;

	size = 104;
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (open_error);
	jolts = (int*)malloc(size * sizeof(int));
	if (jolts == NULL)
		return (malloc_error);
	ret = 1;
	jolts[0] = 0;
	size = 1;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (gnl_error);
		jolts[size] = ft_atoi(line);
		size++;
		free(line);
	}
	sort_int_table(jolts, size);
	jolts[size] = jolts[size - 1] + 3;
	size++;
	// printf("result: %d\n", get_differences(jolts, size));
	if (get_routes(jolts, size) == malloc_error)
	{
		free(jolts);
		return (malloc_error);
	}
	free(jolts);
	return (success);
}

int	main(void)
{
	int	ret;

	ret = read_in_data("input.txt");
	if (ret != success)
		ft_perror(ret);
	return (0);
}
