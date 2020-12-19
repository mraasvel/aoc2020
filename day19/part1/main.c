/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 08:26:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/19 10:21:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day19.h"

/*
** Recursive backtracking function to go through all rules and subrules.
** We need an index to know where in the string we are.
** Because we might reach a point where we have found a mistake,
** we should be able to backtrack and try another possibility.
*/

int	validate_message(char *message, int type, int index)
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
	i = 0;
	store = index;
	// loop through all subrules for each rule
	while (rules[type].sub_rules[i][0] != 0)
	{
		j = 0;
		while (rules[type].sub_rules[i][j] != 0)
		{
			// new type will be whatever integer is int he sub_rules array
			// index will only be incremented if an "endpoint" is found and this matches
			ret = validate_message(message, rules[type].sub_rules[i][j], index);
			if (ret > 0)
				index += ret;
			else
				break ;
			j++;
		}
		// if the entire sub_rule matches in the string, we should return the new index.
		if (type == 0 && message[index] != '\0')
			return (0);
		if (ret > 0)
			return (index - store);
		// when i increments, we should reset the string index to it's initial value
		index = store;
		i++;
	}
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
		if (validate_message(line, 0, 0) > 0)
		{
			valid_count++;
			printf("valid: %s\n", line);
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
