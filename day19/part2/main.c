/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 08:26:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/19 12:07:14 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day19.h"

/*
** Recursive backtracking function to go through all rules and subrules.
** We need an index to know where in the string we are.
** Because we might reach a point where we have found a mistake,
** we should be able to backtrack and try another possibility.
*/

int	validate_message(char *message, int type, int index, int id)
{
	int	i, j;
	int	store, ret;

	// check if we reached a character and if it matches the one in the msg.
	if (rules[type].endpoint != '\0')
	{
		if (message[index] == rules[type].endpoint)
			return (1);
		else
			return (0);
	}
	if (id > 0 && (type == 8 || type == 11))
		i = 1;
	else
		i = 0;
	store = index;
	// loop through all subrules for each rule
	while (rules[type].sub_rules[i][0] != 0)
	{
		j = 0;
		while (rules[type].sub_rules[i][j] != 0)
		{
			// new type will be whatever integer is in the sub_rules array
			// index will only be incremented if an "endpoint" is found and this matches
			ret = validate_message(message, rules[type].sub_rules[i][j], index, id - 1);
			if (rules[type].sub_rules[i][j + 1] != 0 && ret > 0 && message[ret + index] == '\0')
				ret = 0;
			if (ret > 0)
				index += ret;
			else
				break ;
			j++;
		}
		if (ret > 0)
			return (index - store);
		// when i increments, we should reset the string index to it's initial value
		index = store;
		i++;
	}
	return (0);
}

// loop 8 num times
int	loop_eight(char *line, int num)
{
	int	ret;

	while (num >= 0)
	{
		ret = validate_message(line, 8, 0, num);
		if (ret == 0)
			return (ret);
		num--;
	}
	return (ret);
}

// loop type=11 until either match or end of message is found.
int	loop_eleven(char *line, int index)
{
	int	ret;
	int	id;

	ret = 1;
	id = 0;
	while (ret > 0)
	{
		ret = validate_message(line, 11, index, id);
		if (ret == 0)
			return (0);
		if (line[index + ret] == '\0')
			return (ret);
		index += ret;
		id++;
	}
	return (ret);
}

// check every possible combination of 8 and 11
int	loop_zero(char *line)
{
	int	id;
	int	ret;
	int	index;

	ret = 1;
	index = 0;
	id = 0;
	while (1)
	{
		ret = loop_eight(line, id);
		if (ret == 0)
			return (0);
		index += ret;
		ret = loop_eleven(line, index);
		if (ret != 0)
			return (ret);
		id++;
	}
	if (line[index] != '\0')
		ret = 0;
	printf("ret: %d\n", ret);
	return (ret);
}

int	read_messages(int fd)
{
	char	*line;
	int		ret;
	int		valid_count;

	ret = 1;
	valid_count = 0;
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
		if (loop_zero(line) > 0)
		{
			valid_count++;
			// printf("valid: %s\n", line);
		}
		free(line);
	}
	printf("Final count: %d\n", valid_count);
	return (0);
}

int	main(void)
{
	int		fd;

	ft_bzero(rules, MAX_RULE * sizeof(t_rule));
	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (-1);
	get_rules(fd);
	read_messages(fd);
	close(fd);
	return (0);
}
