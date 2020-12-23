/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day23.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/23 08:21:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/23 11:57:42 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY23_H
# define DAY23_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "libvect.h"

# define PATH "../input.txt"


// # define LABELS "247819356" // INPUT
# define LABELS "389125467" // SAMPLE

# define MIN 1
# define MAX 1000000
# define MILLION 1000000
# define MOVE_COUNT 10000000

typedef struct	s_cups
{
	int				cup;
	struct s_cups	*next;
}				t_cups;

t_cups	*list_create(int value);
void	list_append(t_cups **start, int value);
void	list_delete(t_cups **start, int value);
t_cups	*list_extract(t_cups **start, t_cups *position, int n);
void	list_clear(t_cups **start);
void	list_insert(t_cups **start, t_cups *position, t_cups *inserted_list);

#endif
