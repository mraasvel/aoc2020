/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   part2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 10:34:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/14 12:45:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

char	**get_mask_permutations(char *mask, size_t *perm_count);
void	*free_mask_permutations(char **mask_permutations, size_t perm_count);

typedef struct	s_memory
{
	char				index[37];
	unsigned long long	value;
	struct s_memory		*next;
}				t_memory;

unsigned long long	twos_pow(int pwr)
{
	unsigned long long	nbr;

	if (pwr == 0)
		return (1);
	nbr = 1;
	while (pwr > 0)
	{
		nbr *= 2;
		pwr--;
	}
	return (nbr);
}

void		*ft_free_list(t_memory **start)
{
	t_memory	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		free(*start);
		*start = tmp;
	}
	return (NULL);
}

t_memory	*is_index_in_list(t_memory *start, char *index)
{
	while (start != NULL)
	{
		if (ft_strcmp(index, start->index) == 0)
			return (start);
		start = start->next;
	}
	return (NULL);
}

t_memory	*ft_list_add_back(t_memory **start, char *index, unsigned long long value)
{
	t_memory	*new;
	t_memory	*find;

	find = is_index_in_list(*start, index);
	if (find != NULL)
	{
		find->value = value;
		return (*start);
	}
	new = (t_memory*)malloc(1 * sizeof(t_memory));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new->index, index, 37);
	new->value = value;
	new->next = NULL;
	if (*start != NULL)
	{
		find = *start;
		while (find->next != NULL)
			find = find->next;
		find->next = new;
	}
	else
	{
		*start = new;
	}
	return (new);
}

void	nbr_to_binary(unsigned long long nbr, char *str)
{
	size_t	i;

	i = 0;
	while (i < 36)
	{
		if (twos_pow(35 - i) <= nbr)
		{
			str[i] = '1';
			nbr -= twos_pow(35 - i);
		}
		else
			str[i] = '0';
		i++;
	}
	str[i] = '\0';
}

void	get_index(char *index, char *str)
{
	str = ft_strchr(str, '[');
	str++;
	nbr_to_binary(ft_atoull(str), index);
}

void	get_index_permutation(char *index_perm, char *index, char *mask_perm)
{
	for (size_t i = 0; i < 36 ; i++)
	{
		if (mask_perm[i] == 'X')
			index_perm[i] = 'X';
		else if (mask_perm[i] == '1')
			index_perm[i] = '1';
		else
			index_perm[i] = index[i];
	}
}

unsigned long long get_sum(t_memory *start)
{
	unsigned long long	sum;
	size_t				mem_count;

	sum = 0;
	mem_count = 0;
	while (start != NULL)
	{
		sum += start->value;
		mem_count++;
		start = start->next;
	}
	printf("memory indexes: %lu\n", mem_count);
	return (sum);
}

int	read_in_file(char *pathname)
{
	int			fd;
	int			ret;
	char		mask[37];
	char		index[37];
	char		index_perm[37];
	char		*line;
	t_memory	*start;
	char		**mask_permutations;
	size_t		perm_count;
	char		**strings;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = 1;
	start = NULL;
	mask_permutations = NULL;
	perm_count = 0;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		strings = ft_split_token(line, " = ");
		free(line);
		if (strings == NULL)
		{
			ft_free_list(&start);
			return (-1);
		}
		if (ft_strcmp(strings[0], "mask") == 0)
		{
			ft_strlcpy(mask, strings[1], 37);
		}
		else
		{
			get_index(index, strings[0]);
			get_index_permutation(index_perm, index, mask);
			if (mask_permutations != NULL)
				free_mask_permutations(mask_permutations, perm_count);
			mask_permutations = get_mask_permutations(index_perm, &perm_count);
			for (size_t i = 0; i < perm_count; i++)
			{
				ft_list_add_back(&start, mask_permutations[i], ft_atoull(strings[1]));
			}
		}
		ft_free_split(strings);
	}
	printf("result: %llu\n", get_sum(start));
	free_mask_permutations(mask_permutations, perm_count);
	ft_free_list(&start);
	return (0);
}

int	main(void)
{
	// read_in_file("test.txt");
	read_in_file("input.txt");
	return (0);
}
