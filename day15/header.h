/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 08:35:08 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/15 08:40:20 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct	s_intvect
{
	int		*table;
	size_t	size;
	size_t	nmemb;
}				t_intvect;

/*
** vectors
*/

t_intvect	*intvect_init(size_t initial_size);
int			intvect_pushback(int num, t_intvect *vector);
void		intvect_free(t_intvect *vector);

#endif
