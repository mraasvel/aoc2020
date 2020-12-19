/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day19.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/19 08:34:37 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/19 11:30:38 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY19_H
# define DAY19_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

#define PATH "input.txt"
#define MAX_RULE 137
#define MAX_PIPE 1

typedef struct	s_rule
{
	int		type;
	int		sub_rules[3][4];
	char	endpoint;
}				t_rule;

t_rule	rules[MAX_RULE];

int		get_rules(int fd);
void	print_rule(int type);

#endif
