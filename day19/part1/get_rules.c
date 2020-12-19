/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_rules.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 09:39:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/19 09:40:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day19.h"

int	get_char(char *subrule, int type)
{
	int	i;

	i = 0;
	while (ft_isalpha(subrule[i]) == 0)
		i++;
	rules[type].endpoint = subrule[i];
	return (0);
}

int	extract_subrules(char *subrule, int type, int n)
{
	int	i;
	int	rcnt;

	i = 0;
	rcnt = 0;
	if (ft_strchr(subrule, '\"') != NULL)
		return (get_char(subrule, type));
	while (subrule[i] != '\0')
	{
		while (subrule[i] == ' ')
			i++;
		if (ft_isdigit(subrule[i]) != 0)
		{
			rules[type].sub_rules[n - 1][rcnt] = ft_atoi(subrule + i);
			rcnt++;
			while (ft_isdigit(subrule[i]) != 0)
				i++;
		}
	}
	return (0);
}

void print_rule(int type)
{
	int	i;
	int	j;

	printf("type: %d: ", rules[type].type);
	i = 0;
	if (rules[type].endpoint != '\0')
		printf("%c", rules[type].endpoint);
	while (rules[type].sub_rules[i][0] != 0)
	{
		if (i != 0)
			printf(" | ");
		j = 0;
		while (rules[type].sub_rules[i][j] != 0)
		{
			if (j != 0)
				printf(" ");
			printf("%d", rules[type].sub_rules[i][j]);
			j++;
		}
		i++;
	}
	printf("\n");
}

int	extract_rule(char *line)
{
	char	**strings;
	int		type;
	int		i;

	if (*line == '\0')
		return (0);
	strings = ft_split_set(line, ":|");
	if (strings == NULL)
		return (-1);
	type = ft_atoi(strings[0]);
	rules[type].type = type;
	i = 1;
	while (strings[i] != NULL)
	{
		extract_subrules(strings[i], type, i);
		i++;
	}
	ft_free_split(strings);
	return (0);
}

int	get_rules(int fd)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (*line == '\0' || extract_rule(line) == -1)
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (0);
}