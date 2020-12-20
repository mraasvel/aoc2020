/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day20.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/20 08:22:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/20 11:16:57 by mraasvel      ########   odam.nl         */
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

typedef enum	e_num
{
	match,
	mismatch,
	taken,
	available,
	success,
	fail
}				t_num;

// s1 = top, s2 = bot, s3 = left, s4 = right
typedef struct	s_image
{
	int			tile;
	char		sides[4][11];
	int			matches[4];
	int			taken;
}				t_image;

t_image	images[SIZE];

int	read_images(int fd);

#endif
