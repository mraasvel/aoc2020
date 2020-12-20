/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 08:21:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 11:14:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day20.h"

int	indexes[5000];

int		get_index(int tile)
{
	return (indexes[tile]);
}

void	ft_strrev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

// they can be flipped and rotated wtf
int	compare_side(char *s1, char *s2)
{
	char	*tmp;

	if (ft_strcmp(s1, s2) == 0)
		return (match);
	tmp = ft_strdup(s2);
	ft_strrev(tmp);
	if (ft_strcmp(s1, tmp) == 0)
	{
		free(tmp);
		return (match);
	}
	free(tmp);
	return (mismatch);
}

int	get_match_count(int index)
{
	for (size_t i = 0; images[i].tile != -1; i++)
	{
		if (i == index)
			continue ;
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				if (compare_side(images[index].sides[j], images[i].sides[k]) == match)
				{
					images[index].matches[j] = match;
				}
			}
		}
	}
}

int	cnt_matches(int index)
{
	int	cnt;

	cnt = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (images[index].matches[i] == match)
			cnt++;
	}
	return (cnt);
}

int	count_possible_matches(void)
{
	size_t	tiles[4];
	int	j;
	int	match_count;
	int	four_count;
	int	three_count;

	j = three_count = four_count = 0;
	for (size_t i = 0; images[i].tile != -1; i++)
	{
		// set index to tile
		indexes[images[i].tile] = i;
		get_match_count(i);
		match_count = cnt_matches(i);
		if (match_count == 2)
		{
			tiles[j] = images[i].tile;
			j++;
		}
		else if (match_count == 3)
			three_count++;
		else
			four_count++;
	}
	printf("Three: %d\nFour: %d\n", three_count, four_count);
	printf("%lu * %lu * %lu * %lu = %lu\n", tiles[0], tiles[1], tiles[2], tiles[3], tiles[0] * tiles[1] * tiles[2] * tiles[3]);
}

int	main(void)
{
	int	fd;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (-1);
	for (size_t i = 0; i < SIZE; i++)
	{
		images[i].sides[0][10] = 0;
		images[i].sides[1][10] = 0;
		images[i].sides[2][10] = 0;
		images[i].sides[3][10] = 0;
		images[i].tile = -1;
		for (size_t j = 0; j < 4; j++)
			images[i].matches[j] = mismatch;
	}
	read_images(fd);
	close(fd);
	count_possible_matches();
	return (0);
}