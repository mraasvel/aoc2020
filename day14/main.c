/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 09:32:41 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/14 10:26:07 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

typedef struct	s_memory
{
	unsigned long long	nbr;
	char				binary[37];
}				t_memory;

int	get_index(char *str)
{
	int	index;

	str = ft_strchr(str, '[');
	str++;
	index = ft_atoi(str);
	return (index);
}

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

void	ft_set_binary(t_memory *mem, int index, char *mask)
{
	size_t				i;
	unsigned long long	result;

	i = 0;
	result = 0;
	while (i < 36)
	{
		if (mask[i] != 'X')
		{
			mem[index].binary[i] = mask[i];
			if (twos_pow(35 - i) <= mem[index].nbr)
				mem[index].nbr -= twos_pow(35 - i);
		}
		else if (twos_pow(35 - i) <= mem[index].nbr)
		{
			mem[index].binary[i] = '1';
			mem[index].nbr -= twos_pow(35 - i);
		}
		else
			mem[index].binary[i] = '0';
		if (mem[index].binary[i] == '1')
			result += twos_pow(35 - i);
		i++;
	}
	mem[index].nbr = result;
}

void	get_sum(int *index_table, int size, t_memory* mem)
{
	int	i;
	unsigned long long sum;

	i = 0;
	sum = 0;
	while (i < size)
	{
		// if (i == size - 1)
		// 	printf("%llu\n", mem[index_table[i]].nbr);
		// else
		// 	printf("%llu + ", mem[index_table[i]].nbr);
	printf("sum: %llu\n", sum);
		sum += mem[index_table[i]].nbr;
		i++;
	}
}
//20901292243991
int	read_in_file(char *pathname)
{
	t_memory	mem[100000];
	int	index_table[472];
	int	cnt;
	int			index;
	int		fd;
	int		ret;
	char	*line;
	char	*mask;
	char	**strings;
	unsigned long long	sum;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = 1;
	mask = 0;
	sum = 0;
	cnt = 0;
	ft_bzero(mem, 100000 * sizeof(t_memory));
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		strings = ft_split_token(line, " = ");
		free(line);
		if (strings == NULL)
			return (-1);
		if (ft_strcmp(strings[0], "mask") == 0)
		{
			if (mask != NULL)
				free(mask);
			mask = ft_strdup(strings[1]);
		}
		else
		{
			index = get_index(strings[0]);
			index_table[cnt] = index;
			if (mem[index].nbr != 0)
				sum -= mem[index].nbr;
			mem[index].nbr = ft_atoull(strings[1]);
			ft_set_binary(mem, index, mask);
			sum += mem[index].nbr;
			cnt++;
		}
		ft_free_split(strings);
	}
	get_sum(index_table, cnt, mem);
	printf("sum : %llu\n", sum);
	return (0);
}

int	main(void)
{
	read_in_file("input.txt");
	// read_in_file("test.txt");
	return (0);
}
