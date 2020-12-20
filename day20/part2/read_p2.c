/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_p2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 09:03:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 13:35:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day20.h"

int	get_piece_data(char *line, int piece_index, int line_number)
{
	int i = 0;
	int j = 0;

	if (line_number == 0)
	{
		while (ft_isdigit(line[i]) == 0)
			i++;
		pieces[piece_index].tile = ft_atoi(line + i);
		return (0);
	}
	for (i = 0; line[i] != 0; i++)
		pieces[piece_index].map[line_number - 1][i] = line[i];
	for (i = 0; i < 4; i++)
		pieces[piece_index].matches[i] = images[piece_index].matches[i];
	return (0);
}

int	read_pieces(int fd)
{
	char	*line;
	int		ret;
	int		i;
	int		j;

	ret = 1;
	i = 0;
	j = 0;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (*line != '\0')
		{
			get_piece_data(line, i, j);
			j++;
		}
		else
		{
			i++;
			j = 0;
		}
		free(line);
	}
	return (0);
}
