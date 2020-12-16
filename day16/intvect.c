/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intvect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 08:35:03 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/16 08:28:33 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include "libft.h"

t_intvect	*intvect_init(size_t initial_size)
{
	t_intvect	*vector;

	if (initial_size == 0)
		initial_size = 2;
	vector = (t_intvect*)malloc(1 * sizeof(t_intvect));
	if (vector == NULL)
		return (NULL);
	vector->table = (int*)malloc(initial_size * sizeof(int));
	if (vector->table == NULL)
	{
		free(vector);
		return (NULL);
	}
	vector->size = initial_size;
	vector->nmemb = 0;
	return (vector);
}

static int	intvect_realloc(t_intvect *vector)
{
	int		*new_table;
	size_t	new_size;

	new_size = vector->size * 2;
	new_table = (int*)malloc(new_size * sizeof(int));
	if (new_table == NULL)
		return (-1);
	ft_memcpy(new_table, vector->table, vector->nmemb * sizeof(int));
	free(vector->table);
	vector->table = new_table;
	vector->size = new_size;
	return (0);
}

void		intvect_free(t_intvect *vector)
{
	free(vector->table);
	free(vector);
}

int			intvect_pushback(int num, t_intvect *vector)
{
	if (vector->nmemb == vector->size)
	{
		if (intvect_realloc(vector) == -1)
			return (-1);
	}
	vector->table[vector->nmemb] = num;
	vector->nmemb += 1;
	return (0);
}
