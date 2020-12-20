/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 09:03:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 10:36:19 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day20.h"

int	get_map_data(char *line, int image_index, int line_number)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line_number == 0)
	{
		while (ft_isdigit(line[i]) == 0)
			i++;
		images[image_index].tile = ft_atoi(line + i);
		return (0);
	}
	images[image_index].sides[2][line_number - 1] = line[0];
	if (line_number == 1 || line_number == 10)
	{
		while (line[i] != '\0')
		{
			if (line_number == 1)
				images[image_index].sides[0][i] = line[i];
			else
				images[image_index].sides[1][i] = line[i];
			i++;
		}
	}
	images[image_index].sides[3][line_number - 1] = line[9];
	return (0);
}

int	read_images(int fd)
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
			get_map_data(line, i, j);
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
