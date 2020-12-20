/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day20.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 08:22:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 18:15:54 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY20_H
# define DAY20_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "libvect.h"

#define PATH "input.txt"
#define WIDTH 10
#define HEIGHT 10
#define SIZE 145
#define SIDELEN 12
#define SIZE_2 10

#define TEST_CORNER1 1951

// #define CORNER1 TEST_CORNER1
#define CORNER1 3643
#define CORNER2 2647
#define CORNER3 1987
#define CORNER4 3089

typedef enum	e_num
{
	top,
	bot,
	left,
	right,
	match,
	mismatch,
	taken,
	available,
	success,
	fail
}				t_num;

// s1 = top, s2 = bot, s3 = left, s4 = right
// orientation = orientation for first part

typedef struct	s_image
{
	int			orientation;
	int			flipped;
	int			tile;
	char		sides[10][11];
	int			matches[4];
	int			taken;
}				t_image;


// flipped: 0 = original; 1 = left to right; 2 = top to bottom
// rotation: 0 = original; 90 = 90 degrees to the right
// if flipped[0] = 1, it was flipped left to right
// if flipped[1] = 1, it was flipped top to bottom
typedef struct	s_pieces
{
	int		tile;
	int		flipped[2];
	int		rotation;
	char	map[10][11];
	int		matches[4];
	int		matching_tiles[SIZE_2];
	int		taken;
}				t_pieces;

t_image		images[SIZE];
t_pieces	pieces[SIZE];
int			indexes[5000];
int			result[SIDELEN][SIDELEN];

int	read_images(int fd);
int	get_index(int tile);
int	get_match_count(int index);
int	read_pieces(int fd);

#endif
