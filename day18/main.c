/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 08:21:19 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/18 09:51:28 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>

size_t	resolve_brace(char *line, int *i);

typedef enum	e_operation
{
	plus,
	times
}				t_operation;

void	print_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != 0)
	{
		printf("%s\n", strings[i]);
		i++;
	}
}

size_t	get_next_expression(char *line, int *i)
{
	size_t	num;
	size_t	sum;
	int		op;

	while (line[*i] == '*' || line[*i] == ' ')
		(*i)++;
	if (line[*i] == '(')
	{
		(*i) += 1;
		sum = resolve_brace(line, i);
	}
	else
	{
		sum = ft_atoi(line + *i);
		while (ft_isdigit(line[*i]) != 0 || line[*i] == ' ')
			(*i)++;
	}
	while (line[*i] != '\0')
	{
		while (line[*i] == ' ')
			(*i)++;
		if (line[*i] == '+')
		{
			(*i) += 2;
			op = plus;
		}
		else if (line[*i] == '*' || line[*i] == ')')
		{
			return (sum);
		}
		if (line[*i] == '(')
		{
			(*i) += 1;
			num = resolve_brace(line, i);
		}
		else
		{
			num = ft_atoi(line + *i);
			while (ft_isdigit(line[*i]) != 0 || line[*i] == ' ')
				(*i)++;
		}
		if (op == plus)
			sum += num;
	}
	return (sum);
}

size_t	resolve_brace(char *line, int *i)
{
	size_t	num;
	size_t	sum;
	int		op;

	if (line[*i] == '(')
	{
		(*i) += 1;
		sum = resolve_brace(line, i);
	}
	else
	{
		sum = ft_atoi(line + *i);
		while (ft_isdigit(line[*i]) != 0 || line[*i] == ' ')
			(*i)++;
	}
	while (line[*i] != '\0')
	{
		while (line[*i] == ' ')
			(*i)++;
		if (line[*i] == ')')
		{
			(*i)++;
			return (sum);
		}
		if (line[*i] == '+')
		{
			op = plus;
			(*i) += 2;
		}
		if (line[*i] == '*')
		{
			op = times;
			num = get_next_expression(line, i);
		}
		else if (line[*i] == '(')
		{
			(*i)++;
			num = resolve_brace(line, i);
		}
		else
		{
			num = ft_atoi(line + *i);
			while (ft_isdigit(line[*i]) != 0 || line[*i] == ' ')
				(*i)++;
		}
		if (op == plus)
			sum += num;
		else
			sum *= num;
	}
	return (sum);
}
/* "1 + 2 + (3 + (4 * 5)) */
size_t	get_sum_of_line(char *line)
{
	int		op;
	size_t	sum;
	size_t	num;
	int		i;

	sum = 0;
	i = 0;
	if (line[i] == '(')
	{
		i++;
		sum = resolve_brace(line, &i);
	}
	else
	{
		sum = ft_atoi(line + i);
		while (ft_isdigit(line[i]) != 0 || line[i] == ' ')
			i++;
	}
	while (line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '+')
		{
			op = plus;
			i += 2;
		}
		if (line[i] == '*')
		{
			op = times;
			num = get_next_expression(line, &i);
		}
		else if (line[i] == '(')
		{
			i++;
			num = resolve_brace(line, &i);
		}
		else
		{
			num = ft_atoi(line + i);
			while (ft_isdigit(line[i]) != 0 || line[i] == ' ')
				i++;
		}
		if (op == plus)
			sum += num;
		else
			sum *= num;
	}
	return (sum);
}

void	test_line(char *line)
{
	char **strings;

	strings = ft_split(line, '*');
	if (strings == NULL)
		return ;
	print_strings(strings);
	ft_free_split(strings);
}

int	read_file(char *pathname)
{
	int		fd;
	int		ret;
	size_t	sum;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = 1;
	sum = 0;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		sum += get_sum_of_line(line);
		printf("sum: %lu\n", sum);
		free(line);
	}
	printf("final: sum: %lu\n", sum);
	return (0);
}

int	main(void)
{
	read_file("input.txt");
	return (0);
}
