/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 08:21:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/16 11:11:21 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "header.h"

#define RULE_COUNT 20
// #define RULE_COUNT 3

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
		printf("%s: %d-%d %d-%d pos: %d\n", rules[i].rule, rules[i].range1[0], rules[i].range1[1], rules[i].range2[0], rules[i].range2[1], rules[i].pos);
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
			return (1);
		}
	}
	return (0);
}

int	check_position(t_intvect *ticket, t_rules *rules)
{
	size_t	j;
	int	num;
	int	pos;
	int	boolean;
	
	// position in rule = j, position in ticket = i
	for (size_t i = 0; i < ticket->nmemb; i++)
	{
		num = ticket->table[i];
		boolean = 0;
		for (j = 0; j < RULE_COUNT; j++)
		{
			if (rules[i].pos != -1)
				continue ;
			printf("num: %d\n", num);
			if (num >= rules[j].range1[0] && num <= rules[j].range1[1])
			{
				boolean++;
				pos = j;
			}
			else if (num >= rules[j].range2[0] && num <= rules[j].range2[1])
			{
				boolean++;
				pos = j;
			}
			if (boolean > 1)
				break ;
		}
		if (boolean == 1 && rules[pos].pos == -1)
		{
			rules[pos].pos = i;
		}
	}
}
// 0 if num is valid in this rule
int	check_num(t_rules rule, int num)
{
	if (num >= rule.range1[0] && num <= rule.range1[1])
		return (0);
	else if (num >= rule.range2[0] && num <= rule.range2[1])
		return (0);
	return (1);
}

int	position_taken(t_rules *rules, int pos)
{
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		if (rules[i].pos == pos)
			return (1);
	}
	return (0);
}
// 0 if all positions are filled
int	positions_filled(t_rules *rules)
{
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		if (rules[i].pos == -1)
			return (1);
	}
	return (0);
}
// 0 if vector can fit into rule
int	check_vector(t_intvect *vector, t_rules rule)
{
	for (size_t i = 0; i < vector->nmemb; i++)
	{
		if (check_num(rule, vector->table[i]) != 0)
			return (1);
	}
	return (0);
}

int	set_position(t_rules *rules, t_intvect **vectors)
{
	int	count;
	int	pos;
	int	taken[20];
	int	ret;

	ft_bzero(taken, 20 * sizeof(int));
	ret = 1;
	while (ret != 0)
	{
		ret = positions_filled(rules);
		printf("%d %d %d\n", taken[0], taken[1], taken[2]);
		// we also have to check a vector only has one possible rule match
		for (size_t i = 0; i < RULE_COUNT; i++)
		{
			if (taken[i] != 0)
				continue ;
			count = 0;
			// check each rule for each vector
			for (size_t j = 0; j < RULE_COUNT; j++)
			{
				if (rules[j].pos != -1)
					continue ;
				if (check_vector(vectors[i], rules[j]) == 0)
				{
					count++;
					pos = j;
				}
			}
			if (count == 1)
			{
				rules[pos].pos = i;
				taken[i] = 1;
			}
		}
		// check each rule (if a rule has only one possible vector match)
		for (size_t i = 0; i < RULE_COUNT; i++)
		{
			if (rules[i].pos != -1)
				continue ;
			count = 0;
			//check each vector for each rule
			for (size_t j = 0; j < RULE_COUNT; j++)
			{
				if (taken[j] != 0)
					continue ;
				// if count = 1, only a single vector can fit into the rule.
				if (check_vector(vectors[j], rules[i]) == 0)
				{
					pos = j;
					count++;
				}
			}
			if (count == 1)
			{
				rules[i].pos = pos;
				taken[pos] = 1;
			}
		}
	}
}

int	print_result(t_rules *rules, t_intvect *my_ticket)
{
	size_t	result;

	result = 1;
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		if (ft_strstr(rules[i].rule, "departure") != 0)
		{
			printf("%d\n", rules[i].pos);
			result *= my_ticket->table[rules[i].pos];
		}
	}
	printf("result: %lu\n", result);
}

int	read_in_file(char *pathname)
{
	int			fd;
	int			ret;
	char		*line;
	t_rules		rules[RULE_COUNT];
	t_intvect	*my_ticket;
	t_intvect	*ticket;
	t_intvect	*vectors[RULE_COUNT];
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
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		vectors[i] = intvect_init(RULE_COUNT);
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
			error_rate = get_invalid_entries(ticket, rules);
			if (error_rate == 0)
			{
				for (size_t i = 0; i < RULE_COUNT; i++)
				{
					intvect_pushback(ticket->table[i], vectors[i]);
				}
			}
		}
		intvect_free(ticket);
		free(line);
	}
	set_position(rules, vectors);
	for (size_t i = 0; i < RULE_COUNT; i++)
	{
		intvect_free(vectors[i]);
	}
	print_rules(rules);
	print_result(rules, my_ticket);
	intvect_free(my_ticket);
	free_rules(rules);
	return (0);
}

int	main(void)
{
	read_in_file("input.txt");
	// read_in_file("test.txt");
	return (0);
}
