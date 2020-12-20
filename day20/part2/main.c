/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 08:21:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 18:18:11 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day20.h"

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
					size_t	l = 0;
					while (pieces[index].matching_tiles[l] != -1)
						l++;
					pieces[index].matching_tiles[l] = images[i].tile;
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
	// printf("Three: %d\nFour: %d\n", three_count, four_count);
	// printf("%lu * %lu * %lu * %lu = %lu\n", tiles[0], tiles[1], tiles[2], tiles[3], tiles[0] * tiles[1] * tiles[2] * tiles[3]);
}

// want to find corner orientation/flip
int	get_corner(int tile)
{
	int index;

	index = get_index(tile);
	for (size_t i = 0; images[i].tile != -1; i++)
	{
		if (i == index)
			continue ;
		
	}
	return (0);
}

void	print_tile(int tile)
{
	int index = get_index(tile);

	printf("TILE: %d\n", pieces[index].tile);
	for (size_t i = 0; i < 10; i++)
	{
		printf("%s\n", pieces[index].map[i]);
	}
	printf("Top matches: %d\n", pieces[index].matches[top]);
	printf("Right matches: %d\n", pieces[index].matches[right]);
	printf("Bot matches: %d\n", pieces[index].matches[bot]);
	printf("Left matches: %d\n", pieces[index].matches[left]);
	printf("Rotated: %d\n", pieces[index].rotation);
	printf("Matching Tiles");
	for (size_t i = 0; i < SIZE_2; i++)
	{
		printf(" %d", pieces[index].matching_tiles[i]);
	}
	printf("\n");
	printf("\n");
}

// flip left to right if 1
// flip top to bottom if 2
int	flip_piece(int index, int flip)
{
	int	swap;

	if (flip == 1)
	{
		for (size_t i = 0; i < 10; i++)
			ft_strrev(pieces[index].map[i]);
		swap = pieces[index].matches[left];
		pieces[index].matches[left] = pieces[index].matches[right];
		pieces[index].matches[right] = swap;
		if (pieces[index].flipped[0] == 0)
			pieces[index].flipped[0] = 1;
		else
			pieces[index].flipped[0] = 0;
		return (0);
	}
	else
	{
		int i, j, k;
		char tmp;

		i = 0;
		while (i < 10)
		{
			j = 0;
			k = 9;
			while (j < k)
			{
				tmp = pieces[index].map[j][i];
				pieces[index].map[j][i] = pieces[index].map[k][i];
				pieces[index].map[k][i] = tmp;
				j++;
				k--;
			}
			i++;
		}
		swap = pieces[index].matches[top];
		pieces[index].matches[top] = pieces[index].matches[bot];
		pieces[index].matches[bot] = swap;
		if (pieces[index].flipped[1] == 0)
			pieces[index].flipped[1] = 1;
		else
			pieces[index].flipped[1] = 0;
	}
	return (0);
}

// only rotates once 90 degrees
int	rotate_piece(int index)
{
	char	tmp_map[10][10];
	int		tmp_matches[4];

	// switch matching location lol
	tmp_matches[top] = pieces[index].matches[left];
	tmp_matches[right] = pieces[index].matches[top];
	tmp_matches[bot] = pieces[index].matches[right];
	tmp_matches[left] = pieces[index].matches[bot];
	pieces[index].matches[top] = tmp_matches[top];
	pieces[index].matches[right] = tmp_matches[right];
	pieces[index].matches[bot] = tmp_matches[bot];
	pieces[index].matches[left] = tmp_matches[left];
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			tmp_map[i][j] = pieces[index].map[9 - j][i];
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			pieces[index].map[i][j] = tmp_map[i][j];
		}
	}
}

// rotate or flip map
int	translate_piece(int index, int tile, int rotation, int flip)
{
	if (index == -1)
		index = get_index(tile);
	if (flip != 0)
	{
		return (flip_piece(index, flip));
	}
	else if (rotation != 0)
	{
		if (rotation == 90)
		{
			rotate_piece(index);
		}
		else if (rotation == 180)
		{
			rotate_piece(index);
			rotate_piece(index);
		}
		else if (rotation == 270)
		{
			rotate_piece(index);
			rotate_piece(index);
			rotate_piece(index);
		}
		pieces[index].rotation += rotation;
		if (pieces[index].rotation >= 360)
			pieces[index].rotation -= 360;
	}
	return (0);
}

int	print_coords(int tile, int x, int y)
{
	return (success);
	printf("%d: (%d, %d)\n", tile, x, y);
}

int	print_top(void)
{
	int x, y;

	// top only prints first 1-9 lines
	y = 0;
	for (size_t i = 0; i < WIDTH - 1; i++)
	{
		for (x = 0; x < SIDELEN; x++)
		{
			if (x == 0)
				printf("%c", pieces[get_index(result[y][x])].map[i][0]);
			for (size_t j = 1; j < WIDTH - 1; j++)
			{
				printf("%c", pieces[get_index(result[y][x])].map[i][j]);
			}
			if (x == SIDELEN - 1)
				printf("%c", pieces[get_index(result[y][x])].map[i][9]);
		}
		printf("\n");
	}
	return (success);
}

int	print_bottom(void)
{
	int x, y;

	y = 11;
	//bottom prints 2-10 lines
	for (size_t i = 1; i < WIDTH; i++)
	{
		for (x = 0; x < SIDELEN; x++)
		{
			if (x == 0)
				printf("%c", pieces[get_index(result[y][x])].map[i][0]);
			for (size_t j = 1; j < WIDTH - 1; j++)
			{
				printf("%c", pieces[get_index(result[y][x])].map[i][j]);
			}
			if (x == SIDELEN - 1)
				printf("%c", pieces[get_index(result[y][x])].map[i][9]);
		}
		printf("\n");
	}
	return (success);
}

int	print_middle(int y)
{
	int	x;

	// middle always prints 2-9 lines
	for (size_t i = 1; i < WIDTH - 1; i++)
	{
		for (x = 0; x < SIDELEN; x++)
		{
			// if (x == 0)
			// 	printf("%c", pieces[get_index(result[y][x])].map[i][0]);
			for (size_t j = 1; j < WIDTH - 1; j++)
			{
				fprintf(stderr, "%c", pieces[get_index(result[y][x])].map[i][j]);
			}
			// if (x == SIDELEN - 1)
			// 	printf("%c", pieces[get_index(result[y][x])].map[i][9]);
		}
		fprintf(stderr, "\n");
	}
}

int	print_map(void)
{
	// if left side: printf 1-8 y and 0-8 x
	// if right side: printf 1-9 y and 1-9 x
	// if tleft corner: printf 0-8 y and 0-8 x
	// if tright corner: printf 0-8 y and 1-9 x
	// if bleft corner: printf 1-9  y and 0-8 x
	// if bright corner: printf 1-9 y and 1-9 x
	for (size_t y = 0; y < SIDELEN; y++)
	{
		// if (y == 0)
		// 	print_top();
		// if (y == SIDELEN - 1)
		// 	print_bottom();
		// if (y != 0 && y != SIDELEN - 1)
			print_middle(y);
	}
	return (success);
}

//compare left side of index to right side of index2
int	compare_left(int index, int index2)
{
	for (size_t i = 0; i < SIZE_2; i++)
	{
		if (pieces[index].map[i][0] != pieces[index2].map[i][9])
			return (fail);
	}
	return (success);
}

//compare top of index to bottom of index2
int	compare_top(int index, int index2)
{
	for (size_t i = 0; i < SIZE_2; i++)
	{
		if (pieces[index].map[0][i] != pieces[index2].map[9][i])
			return (fail);
	}
	return (success);
}

int	check_adjacents(int index, int x, int y)
{
	if (x == 0 && y == 0)
		return (success);
	if (x == 0 && pieces[index].matches[left] == match)
		return (fail);
	if (y == 0 && pieces[index].matches[top] == match)
		return (fail);
	if (x == SIDELEN - 1 && pieces[index].matches[right] == match)
		return (fail);
	if (y == SIDELEN - 1 && pieces[index].matches[bot] == match)
		return (fail);
	// check if position is valid
	// if (((y != 0 && x != 0) && (x != SIDELEN - 1 && y != SIDELEN - 1)) && cnt_matches(index) != 4)
	// 	return (fail);
	if (x != 0 && compare_left(index, get_index(result[y][x - 1])) == success)
		return (success);
	if (y != 0 && compare_top(index, get_index(result[y - 1][x])) == success)
		return (success);
	// printf("checking: %d\n", pieces[index].tile);
	return (fail);
}

// start tile = first corner
int	backtracking_bullshit(int tile, int x, int y)
{
	int	index;
	int	next_index;

	index = get_index(tile);
	if (x == SIDELEN && y == SIDELEN)
	{
		return (success);
	}
	if (x == SIDELEN)
	{
		x = 0;
		y++;
	}
	if (check_adjacents(index, x, y) == fail)
		return (fail);
	if (x == SIDELEN - 1 && y == SIDELEN - 1)
	{
		result[y][x] = tile;
		return (success);
	}
	if (x == SIDELEN - 1)
	{
		// pick next piece by looking at [y][0]
		index = get_index(result[y][0]);
	}
	// try next tile by rotating potential adjacent tiles until they fit and match it.
	for (size_t i = 0; pieces[index].matching_tiles[i] != -1; i++)
	{
		next_index = get_index(pieces[index].matching_tiles[i]);
		result[y][x] = tile;
		if (pieces[next_index].taken == 1)
			continue ;
		// 8 possible permutations of a squares
		pieces[next_index].taken = 1;
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (success);
		translate_piece(next_index, 0, 0, 1);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (success);
		translate_piece(next_index, 0, 0, 1);
			translate_piece(next_index, 0, 90, 0);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (success);
		translate_piece(next_index, 0, 0, 1);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (success);
		translate_piece(next_index, 0, 0, 1);
			translate_piece(next_index, 0, 90, 0);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (success);
		translate_piece(next_index, 0, 0, 1);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (print_coords(tile, x, y));
		translate_piece(next_index, 0, 0, 1);
			translate_piece(next_index, 0, 90, 0);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (print_coords(tile, x, y));
		translate_piece(next_index, 0, 0, 1);
		if (backtracking_bullshit(pieces[index].matching_tiles[i], x + 1, y) == success)
			return (print_coords(tile, x, y));
		translate_piece(next_index, 0, 0, 1);
		translate_piece(next_index, 0, 90, 0);
		result[y][x] = -1;
		pieces[next_index].taken = 0;
	}
	return (fail);
}

void	print_results()
{
	for (size_t i = 0; i < SIDELEN; i++)
	{
		for (size_t j = 0; j < SIDELEN; j++)
		{
			if (j != 0)
				printf(" ");
			printf("%d", result[i][j]);
		}
		printf("\n");
	}
}

int	main(void)
{
	int	fd;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (-1);
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < 4; j++)
			images[i].sides[j][10] = 0;
		images[i].tile = -1;
		for (size_t j = 0; j < 4; j++)
			images[i].matches[j] = mismatch;
		for (size_t j = 0; j < SIZE_2; j++)
			pieces[i].matching_tiles[j] = -1;
		pieces[i].tile = -1;
		pieces[i].flipped[0] = 0;
		pieces[i].flipped[1] = 0;
		pieces[i].rotation = 0;
		pieces[i].taken = 0;
	}
	for (size_t i = 0; i < SIDELEN; i++)
	{
		for (size_t j = 0; j < SIDELEN; j++)
		{
			result[i][j] = -1;
		}
	}

	read_images(fd);
	close(fd);
	count_possible_matches();
	fd = open(PATH, O_RDONLY);
	read_pieces(fd);
	close(fd);
	// translate_piece(-1, CORNER1, 0, 2);
	translate_piece(-1, CORNER1, 90, 0);
	// print_tile(CORNER1);
	pieces[get_index(CORNER1)].taken = 1;
	if (backtracking_bullshit(CORNER1, 0, 0) == fail)
		printf("FAILED\n");
	print_results();
	print_map();
	return (0);
}
