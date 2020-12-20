/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_dragons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 16:28:53 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 21:09:50 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define PT "output.txt"
#include "day20.h"

const char *dragon[] = {
	"xxxxxxxxxxxxxxxxxx#x",
	"#xxxx##xxxx##xxxx###",
	"x#xx#xx#xx#xx#xx#xxx"
};

int	dragon_hash_count = 0;

int	dragon_count = 0;
#define LEN 97
char map[96][97];

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

int	compare_dragon(int x, int y)
{
	int	cnt;

	cnt = 0;
	for (size_t i = 0; i < 3; i++)
	{
		if (i + y > LEN + 1)
			return (fail);
		for (size_t j = 0; j < 20; j++)
		{
			if (j + x > LEN + 1)
				return (fail);
			if (dragon[i][j] == 'x')
				continue ;
			if (map[y + i][x + j] != '#')
				return (fail);
			else
				cnt++;
		}
	}
	dragon_hash_count += cnt;
	return (success);
}

int	find_dragon_in_map(void)
{
	int	cnt;

	cnt = 0;
	for (size_t y = 0; y < LEN - 1; y++)
	{
		for (size_t x = 0; x < LEN - 1; x++)
		{
			if (compare_dragon(x, y) == success)
			{
				cnt++;
			}
		}
	}
	if (cnt > 0)
		dragon_count = cnt;
	return (cnt);
}

// flip == 1: left to right
int	flip_piece(int flip)
{
	if (flip == 1)
	{
		for (size_t i = 0; i < LEN - 1; i++)
		{
			ft_strrev(map[i]);
		}
	}
	return (0);
}

// only rotates once 90 degrees
int	rotate_map(void)
{
	char	tmp_map[LEN - 1][LEN];

	for (size_t i = 0; i < LEN - 1; i++)
	{
		for (size_t j = 0; j < LEN - 1; j++)
		{
			tmp_map[i][j] = map[LEN - j - 2][i];
		}
	}
	for (size_t i = 0; i < LEN - 1; i++)
	{
		for (size_t j = 0; j < LEN - 1;j++)
		{
			map[i][j] = tmp_map[i][j];
		}
	}
}

// rotate or flip map
int	translate_map(int rotation, int flip)
{
	if (flip != 0)
	{
		return (flip_piece(flip));
	}
	else if (rotation != 0)
	{
		if (rotation == 90)
		{
			rotate_map();
		}
		else if (rotation == 180)
		{
			rotate_map();
			rotate_map();
		}
		else if (rotation == 270)
		{
			rotate_map();
			rotate_map();
			rotate_map();
		}
	}
	return (0);
}

void	print_map()
{
	for (size_t i = 0; i < LEN - 1; i++)
	{
		printf("%s\n", map[i]);
	}
}

int	count_hash_in_map(void)
{
	int	cnt;

	cnt = 0;
	for (size_t i = 0; i < LEN - 1; i++)
	{
		for (size_t j = 0; j < LEN - 1; j++)
		{
			if (map[i][j] == '#')
				cnt++;
		}
	}
	printf("hashes in map: %d\n", cnt);
	printf("dragon hash: %d\n", dragon_hash_count);
	printf("cnt: %d\n", cnt - dragon_hash_count);
	return (cnt);
}

int	cnt_hash(char *line)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (line[i] != 0)
	{
		if (line[i] == '#')
			cnt++;
		i++;
	}
	return (cnt);
}

int	main(void)
{
	int	fd;
	char *line;
	int	hashes;

	hashes = 0;
	fd = open(PT, O_RDONLY);
	for (size_t i = 0; i < 98; i++)
	{
		ft_getline(fd, &line);
		if (*line == 0)
		{
			free(line);
			break ;
		}
		hashes += cnt_hash(line);
		ft_memcpy(map[i], line, 99);
		free(line);
	}
	printf("hashes: %d\n", hashes);
	find_dragon_in_map();

	translate_map(0, 1);
	find_dragon_in_map();
	translate_map(0, 1);

	translate_map(90, 0);
	find_dragon_in_map();
	translate_map(0, 1);
	find_dragon_in_map();
	translate_map(0, 1);

	translate_map(90, 0);
	find_dragon_in_map();
	translate_map(0, 1);
	find_dragon_in_map();
	translate_map(0, 1);

	translate_map(90, 0);
	find_dragon_in_map();
	translate_map(0, 1);
	find_dragon_in_map();
	count_hash_in_map();
	return (0);
}