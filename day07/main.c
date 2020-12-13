/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 12:37:03 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/07 16:06:47 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "adv.h"

int	get_contain_size(char **strings)
{
	int	count;

	count = 0;
	while (*strings != NULL)
	{
		if (ft_isdigit(**strings) != 0)
			count++;
		strings++;
	}
	return (count);
}

int	process_line_data(char *line, t_top *bags)
{
	char	**strings;
	int		i;
	int		contain_index;

	strings = ft_split_set(line, " ,");
	if (strings == NULL)
		return (-1);
	bags->type = ft_join_n_strings(3, strings[0], " ", strings[1]);
	if (bags->type == NULL)
	{
		ft_free_split(strings);
		return (-1);
	}
	bags->contain_size = get_contain_size(strings);
	bags->contain = (t_contain*)malloc((bags->contain_size) * sizeof(t_contain));
	if (bags->contain == NULL)
	{
		ft_free_split(strings);
		free(bags->type);
		return (-1);
	}
	i = 0;
	contain_index = 0;
	while (strings[i] != NULL)
	{
		if (ft_isdigit(strings[i][0]) != 0)
		{
			bags->contain[contain_index].amount = ft_atoi(strings[i]);
			bags->contain[contain_index].type = ft_join_n_strings(3, strings[i + 1], " ", strings[i + 2]);
			if (bags->contain[contain_index].type == NULL)
			{
				while(contain_index > 0)
				{
					contain_index--;
					free(bags->contain[contain_index].type);
				}
				free(bags->contain);
				free(bags->type);
				ft_free_split(strings);
				return (-1);
			}
			contain_index++;
			i += 2;
		}
		i++;
	}
	ft_free_split(strings);
	return (0);
}

int	free_bags(t_top *bags, int i)
{
	while (i > 0)
	{
		i--;
		while (bags[i].contain_size > 0)
		{
			bags[i].contain_size--;
			free(bags[i].contain[bags[i].contain_size].type);
		}
		free(bags[i].contain);
		free(bags[i].type);
	}
	return (-1);
}

/*
** 1. Find occurance of type in each bottom.
** 2. set "taken" to 1 and add 1 to return count.
** 2. Then call same function with that top.. etc
*/

int	find_occurances_of_bag(t_top *bags, char *type)
{
	int	count;
	int	ci;
	int	i;

	count = 0;
	i = 0;
	while (i < 594)
	{
		if (bags[i].taken == 0)
		{
			ci = 0;
			while (ci < bags[i].contain_size)
			{
				if (ft_strcmp(type, bags[i].contain[ci].type) == 0)
				{
					bags[i].taken = 1;
					count++;
					count += find_occurances_of_bag(bags, bags[i].type);
					break ;
				}
				ci++;
			}
		}
		i++;
	}
	return (count);
}

int	find_subbag_count(t_top *bags, char *type)
{
	int	count;
	int	amount;
	int	subbags;
	int	ci;
	int	i;

	count = 0;
	i = 0;
	while (i < 594)
	{
		if (ft_strcmp(type, bags[i].type) == 0)
		{
			ci = 0;
			while (ci < bags[i].contain_size)
			{
				amount = bags[i].contain[ci].amount;
				subbags = find_subbag_count(bags, bags[i].contain[ci].type);
				if (amount != 0 && subbags != 0)
					amount = amount + amount * subbags;
				count += amount;
				ci++;
			}
		}
		i++;
	}
	return (count);
}

void	print_bags(t_top *bags)
{
	int	i;
	int	ci;

	i = 0;
	while (i < 594)
	{
		printf("%s", bags[i].type);
		ci = 0;
		while (ci < bags[i].contain_size)
		{
			printf(":");
			printf("%d", bags[i].contain[ci].amount);
			printf(":%s", bags[i].contain[ci].type);
			ci++;
		}
		printf("\n");
		i++;
	}
}

int	read_in_data(char *pathname)
{
	int		fd;
	int		ret;
	char	*line;
	t_top	bags[594];
	int		index;
	int		cnt;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("fd error\n");
		return (-1);
	}
	ret = 1;
	index = 0;
	for (int i = 0; i < 594; i++)
	{
		bags[i].taken = 0;
		bags[i].contain_size = 0;
	}
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			printf("GNL error\n");
			return (-1);
		}
		if (*line != '\0')
		{
			if (process_line_data(line, (bags + index)) == -1)
			{
				free_bags(bags, index);
				free(line);
				return (-1);
			}
			index++;
		}
		free(line);
	}
	cnt = find_occurances_of_bag(bags, "shiny gold");
	// cnt = find_subbag_count(bags, "shiny gold");
	// print_bags(bags);
	free_bags(bags, index);
	return (cnt);
}

int	main(void)
{
	int	cnt;

	cnt = read_in_data("tijmen_input");
	printf("cnt: %d\n", cnt);
	return (0);
}
