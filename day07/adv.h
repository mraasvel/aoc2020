/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   adv.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/07 12:53:54 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/07 13:18:37 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADV_H
# define ADV_H

typedef struct	s_contain
{
	char	*type;
	int		amount;
}				t_contain;

typedef struct	s_top
{
	char		*type;
	int			taken;
	int			contain_size;
	t_contain	*contain;
}				t_top;

#endif
