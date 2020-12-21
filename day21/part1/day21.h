/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day21.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:23:51 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/21 08:55:21 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY21_H
# define DAY21_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "libvect.h"

# define PATHNAME "../sample.txt"
// # define PATHNAME "../input.txt"

# define FOOD_SIZE 1000
# define ALLERGEN_SIZE 100

typedef struct	s_food
{
	char		name[100];
	int			key;
}				t_food;

typedef struct	s_allergen
{
	char	name[100];
	int		food_index[FOOD_SIZE];
}				t_allergen;

#endif
