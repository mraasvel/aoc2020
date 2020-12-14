/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   permute_mask.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 11:10:17 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/14 12:18:07 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int		count_x(char *mask)
{
	int	cnt, i;

	cnt = i = 0;
	while (i < 36)
	{
		if (mask[i] == 'X')
			cnt++;
		i++;
	}
	return (cnt);
}

static void	permute_mask(char **mask_permutations, int *m_i, char *mask, int j, int x_count, int *x_indexes)
{
	int	i;

	i = 0;
	if (j == x_count)
	{
		if (*m_i != ft_pow(2, x_count) - 1)
			ft_strlcpy(mask_permutations[*m_i + 1], mask_permutations[*m_i], 37);
		(*m_i)++;
		return ;
	}
	while (i < 2)
	{
		mask_permutations[*m_i][x_indexes[j]] = '0' + i;
		permute_mask(mask_permutations, m_i, mask, j + 1, x_count, x_indexes);
		i++;
	}
}
char	**get_mask_permutations(char *mask, size_t *perm_count)
{
	char	**mask_permutations;
	int		x_count;
	int	m_i;

	x_count = count_x(mask);
	int		x_indexes[x_count];
	x_count = 0;
	for (int i = 0; i < 36; i++)
	{
		if (mask[i] == 'X')
		{
			x_indexes[x_count] = i;
			x_count++;
		}
	}
	*perm_count = (unsigned long long)ft_pow(2, x_count);
	mask_permutations = (char**)malloc((*perm_count + 1) * sizeof(char*));
	if (mask_permutations == NULL)
		return (NULL);
	for (int i = 0; i < *perm_count; i++)
	{
		mask_permutations[i] = (char*)malloc(37 * sizeof(char));
		// fuck memory management btw
		if (mask_permutations[i] == NULL)
			return (NULL);
		ft_strlcpy(mask_permutations[i], mask, 37);
	}
	m_i = 0;
	permute_mask(mask_permutations, &m_i, mask, 0, x_count, x_indexes);
	return (mask_permutations);
}

void	*free_mask_permutations(char **mask_permutations, size_t perm_count)
{
	for (size_t i = 0; i < perm_count; i++)
	{
		free(mask_permutations[i]);
	}
	free(mask_permutations);
}
static void	print_permutations(char **permutations, size_t perm_count)
{
	for (size_t i = 0; i < perm_count; i++)
	{
		printf("%s\n", permutations[i]);
	}
	printf("count: %ld\n", perm_count);
}

// //X's are wildcards and can be either a 0 or a 1.
// int	main(void)
// {
// 	char	**mask_permutations;
// 	size_t	perm_count;
	
// 	mask_permutations = get_mask_permutations("01111X0011X11110XX11X110111001X00001", &perm_count);
// 	free_mask_permutations(mask_permutations, perm_count);
// 	return (0);
// }