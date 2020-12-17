/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day17.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 08:40:56 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/17 14:00:39 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY17_H
# define DAY17_H

# define TABLE_SIZE 10000
# include <stddef.h>
# include <stdio.h>

typedef enum	e_nums
{
	success,
	error,
	active,
	inactive
}				t_nums;

typedef struct	s_vector
{
	int	x;
	int	y;
	int	z;
	int	w;
}				t_vector;

typedef struct	s_cube
{
	t_vector	coord;
	int			status;
	int			neighbor_count;
}				t_cube;

typedef struct	s_LinkedList
{
	t_cube				data;
	struct s_LinkedList	*next;
}				LinkedList;

/* main.c */

t_vector	get_vector(int x, int y, int z, int w);
void	print_vector(t_vector vector);

/* Hash Table Functions */

void	hashtable_init(LinkedList *hashtable);
int		hash_fetch(LinkedList *hashtable, t_vector key);
int		hash_insert(LinkedList *hashtable, t_vector key);
void	hash_delete(LinkedList *hashtable, t_vector key);
int		hash_key_match(t_vector a, t_vector b);
void	hash_free(LinkedList *hashtable);

size_t	hash(t_vector key);

/* LinkedList Functions */

LinkedList	*find_key_in_list(t_vector key, LinkedList *element);
LinkedList	*create_new_entry(t_vector key);
void		free_linkedlist(LinkedList *start);
void		delete_key_from_list(t_vector key, LinkedList *prev, LinkedList *start);
int			get_list_size(LinkedList *start);

/* util.c */

int	ft_max(int a, int b);
int	ft_min(int a, int b);

#endif
