/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 08:21:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/16 09:16:22 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "header.h"

// #define RULE_COUNT 20
#define RULE_COUNT 3

typedef struct	s_rules
{
	int		range1[2];
	int		range2[2];
	int		pos;
	char	*rule;
}				t_rules;

int	extract_rules(char *line, t_rules *rules, int i)
{
	char	**strings;
	int		j;

	strings = ft_split(line, ':');
	if (strings == NULL)
		return (-1);
	rules[i].range1[0] = ft_atoi(strings[1] + 1);
	j = 0;
	while (strings[1][j] != '-')
		j++;
	rules[i].range1[1] = ft_atoi(strings[1] + j + 1);
	while (strings[1][j] == '-' || ft_isdigit(strings[1][j]) != 0)
		j++;
	j += 4;
	rules[i].range2[0] = ft_atoi(strings[1] + j);
	while (strings[1][j] != '-')
		j++;
	rules[i].range2[1] = ft_atoi(strings[1] + j + 1);
	rules[i].rule = ft_strdup(strings[0]);
	ft_free_split(strings);
	if (rules[i].rule == NULL)
		return (-1);
	return (0);
}

int	get_rules(char *pathname, t_rules *rules)
{
	int		fd;
	int		ret;
	int		e_ret;
	int		i;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (*line == '\0')
		{
			free(line);
			break ;
		}
		e_ret = extract_rules(line, rules, i);
		rules[i].pos = -1;
		i++;
		free(line);
		if (e_ret == -1)
			return (-1);
	}
	return (fd);
}

void	print_rules(t_rules *rules)
{
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		printf("%s: %d-%d %d-%d\n", rules[i].rule, rules[i].range1[0], rules[i].range1[1], rules[i].range2[0], rules[i].range2[1]);
	}
	
}
void	free_rules(t_rules *rules)
{
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		free(rules[i].rule);
	}
}

int	get_own_ticket(int fd, t_intvect *ticket)
{
	char	*line;
	char	**strings;

	ft_getline(fd, &line);
	free(line);
	ft_getline(fd, &line);
	strings = ft_split(line, ',');
	if (strings == NULL)
		return (-1);
	for (size_t i = 0; strings[i] != NULL; i++)
	{
		intvect_pushback(ft_atoi(strings[i]), ticket);
	}
	free(line);
	ft_getline(fd, &line);
	free(line);
	ft_getline(fd, &line);
	free(line);
	ft_free_split(strings);
	return (0);
}

int	get_ticket(t_intvect *ticket, char *line)
{
	char	**strings;

	strings = ft_split(line, ',');
	if (strings == NULL)
		return (-1);
	for (size_t i = 0; strings[i] != NULL; i++)
	{
		intvect_pushback(ft_atoi(strings[i]), ticket);
	}
	ft_free_split(strings);
	return (0);
}

// return 0 for valid, 1 for invalid
int		is_invalid_range(int num, t_rules *rules)
{
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		if (num >= rules[i].range1[0] && num <= rules[i].range1[1])
			return (0);
		else if (num >= rules[i].range2[0] && num <= rules[i].range2[1])
			return (0);
	}
	return (1);
}

size_t	get_invalid_entries(t_intvect *ticket, t_rules *rules)
{
	size_t	total;

	total = 0;
	for (size_t i = 0; i < ticket->nmemb; i++)
	{
		if (is_invalid_range(ticket->table[i], rules) == 1)
		{
			total += ticket->table[i];
		}
	}
	return (total);
}

int	read_in_file(char *pathname)
{
	int			fd;
	int			ret;
	char		*line;
	t_rules		rules[RULE_COUNT];
	t_intvect	*my_ticket;
	t_intvect	*ticket;
	size_t		error_rate;

	fd = get_rules(pathname, rules);
	if (fd == -1)
		return (-1);
	my_ticket = intvect_init(0);
	if (my_ticket == NULL)
	{
		intvect_free(my_ticket);
		free_rules(rules);
		return (-1);
	}
	get_own_ticket(fd, my_ticket);
	ret = 1;
	error_rate = 0;
	while (ret > 0)
	{
		ticket = intvect_init(32);
		if (ticket == NULL)
		{
			free_rules(rules);
			intvect_free(my_ticket);
			return (-1);
		}
		ret = ft_getline(fd, &line);
		if (ret == -1)
		{
			free_rules(rules);
			intvect_free(my_ticket);
			intvect_free(ticket);
			return (-1);
		}
		if (*line != '\0')
		{
			if (get_ticket(ticket, line) == -1)
			{
				free(line);
				intvect_free(my_ticket);
				intvect_free(ticket);
				free_rules(rules);
				return (-1);
			}
			error_rate += get_invalid_entries(ticket, rules);
		}
		intvect_free(ticket);
		free(line);
	}
	print_rules(rules);
	printf("error: %lu\n", error_rate);
	intvect_free(my_ticket);
	free_rules(rules);
	return (0);
}

int	main(void)
{
	// read_in_file("input.txt");
	read_in_file("test.txt");
	return (0);
}
