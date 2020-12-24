/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day24.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/24 08:30:44 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/24 12:36:01 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY24_H
# define DAY24_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "libvect.h"
# include <limits.h>

# define PATH "../input.txt"

# define TABLE_SIZE 1000
# define DAYS 100

typedef enum	e_nums
{
	error,
	success,
	black,
	white
}				t_nums;

typedef struct	s_pair
{
	int	x;
	int	y;
}				t_pair;

typedef struct	s_data
{
	t_pair	key;
	int		status;
}				t_data;

typedef struct	s_LinkedList
{
	t_data				data;
	struct s_LinkedList	*next;
}				LinkedList;

/*
** hash.c
*/

void	hashtable_init(LinkedList *hashtable);
void	hashtable_free(LinkedList *hashtable);
int		hash_key_match(t_pair a, t_pair b);
int		hash_insert(t_pair key, LinkedList *hashtable);
int		hash_get(t_pair key, LinkedList *hashtable);

/*
** list.c
*/

LinkedList	*list_free(LinkedList *hashtable);
LinkedList	*find_key(LinkedList *hashtable, t_pair key);
int			list_add_front(LinkedList *hashtable, t_pair key);


#endif
