/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 08:22:17 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/06 09:23:28 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"

int	count_group(char *line)
{
	static char	ascii[27];
	char		ascii_person[26];
	int			i;
	int			sum;

	sum = 0;
	if (*line == '\0')
	{
		for (int j = 0; j < 26; j++)
		{
			if (ascii[j] == ascii[26])
				sum++;
		}
		ft_bzero(ascii, 27 * sizeof(char));
		return (sum);
	}
	ascii[26] += 1;
	i = 0;
	ft_bzero(ascii_person, 26 * sizeof(char));
	while (line[i] != '\0')
	{
		if (ascii_person[line[i] - 'a'] == 0)
			ascii_person[(int)line[i] - 'a'] = 1;
		i++;
	}
	for (int j = 0; j < 26; j++)
		ascii[j] += ascii_person[j];
	return (0);
}

int	read_in_file(char *pathname)
{
	char	*line;
	int		fd;
	int		ret;
	int		sum;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("open error\n");
		return (-1);
	}
	ret = 1;
	sum = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			printf("GNL error\n");
			return (-1);
		}
		// do stuff with line
		sum += count_group(line);
		free(line);
	}
	return (sum);
}

int	main(void)
{
	int	sum;

	sum = read_in_file("input.txt");
	// sum = read_in_file("test.txt");
	printf("sum: %d\n", sum);
	return (0);
}
