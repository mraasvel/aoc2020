/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 08:26:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/02 08:55:15 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

typedef enum	e_errnum
{
	malloc_error = -255,
	write_error,
	open_error,
	read_error,
	invalid_pw,
	valid_pw,
	success
}				t_errnum;

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

int	get_letter_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != 0)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

/*
** Format:
** "1-4 n: nnnnn"
** strings[0]: range start
** strings[1]: range end
** strings[2]: letter to appear
** strings[3]: password
*/

int	check_password_validity(char *line)
{
	char	**strings;
	int		min;
	int		max;
	char	letter;
	int		count;

	strings = ft_split_set(line, " :-");
	if (strings == NULL)
		return (malloc_error);
	min = ft_atoi(strings[0]);
	max = ft_atoi(strings[1]);
	letter = strings[2][0];
	if (strings[3][min - 1] == letter && strings[3][max - 1] == letter)
	{

		free_strings(strings);
		return (invalid_pw);
	}
	if (strings[3][min - 1] != letter && strings[3][max - 1] != letter)
	{
		free_strings(strings);
		return (invalid_pw);
	}
	free_strings(strings);
	return (valid_pw);
}

int	read_in_file(char *pathname)
{
	int		fd;
	int		ret;
	int		count;
	int		pw_ret;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		return (open_error);
	}
	ret = 1;
	count = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			fprintf(stderr, "GNL error\n");
			return (read_error);
		}
		pw_ret = check_password_validity(line);
		if (pw_ret == valid_pw)
		{
			// fprintf(stderr, "valid pw: %s\n", line);
			count++;
		}
		// if (pw_ret == invalid_pw)
		// 	fprintf(stderr, "invalid password: %s\n", line);
		free(line);
		if (pw_ret == malloc_error)
			return (malloc_error);
	}
	return (count);
}

int	main(void)
{
	int	ret;

	ret = read_in_file("input.txt");
	if (ret < 0)
	{
		fprintf(stderr, "error\n");
		return (0);
	}
	fprintf(stdout, "Valid password count: %d\n", ret);
	return (0);
}
