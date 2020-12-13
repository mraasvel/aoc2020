/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 11:18:03 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/08 12:55:21 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

typedef struct	s_instructions
{
	char	*type;
	int		value;
	int		executed;
}				t_instructions;

void	free_instructions(t_instructions *inst, int i)
{
	while (i > 0)
	{
		i--;
		free(inst[i].type);
	}
}

int	extract_instruction(t_instructions *inst, char *line)
{
	char	**strings;

	strings = ft_split(line, ' ');
	if (strings == NULL)
		return (-1);
	inst->type = ft_strdup(strings[0]);
	if (inst->type == NULL)
	{
		ft_free_split(strings);
		return (-1);
	}
	inst->value = ft_atoi(strings[1]);
	inst->executed = 0;
	ft_free_split(strings);
	return (0);
}

int	execute_instructions(t_instructions *inst)
{
	int	i;
	int	acc;
	int	total;

	i = 0;
	acc = 0;
	total = 0;
	while (i < 642)
	
	{
		inst[i].executed = 0;
		i++;
	}
	i = 0;
	while (i < 642)
	{
		total++;
		if (inst[i].executed == 1)
		{
			printf("FAIL: inst[%d]: %s - total: |%d|\n", i, inst[i].type, total);
			return (-1);
		}
		inst[i].executed = 1;
		if (ft_strcmp(inst[i].type, "acc") == 0)
			acc += inst[i].value;
		else if (ft_strcmp(inst[i].type, "jmp") == 0)
		{
			i += inst[i].value;
			continue ;
		}
		i++;
	}
	printf("exited successfully\n");
	return (acc);
}

void	swap_strings(char *a, char *b)
{
	int	i;
	char	tmp;

	i = 0;
	while (a[i] != 0 && b[i] != 0)
	{
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
		i++;
	}
}

int	brute_force(t_instructions *inst)
{
	int		fd;
	char	*line;
	int cnt;
	int		ret;
	int		i;
	int		acc;
	char	**strings;
	char	nop[4];
	char	jmp[4];

	fd = open("loop", O_RDONLY);
	if (fd == -1)
	{
		printf("second fd error\n");
		return (-1);
	}
	ret = 1;
	acc = i = 0;
	ft_strlcpy(jmp, "jmp", 4);
	ft_strlcpy(nop, "nop", 4);
	cnt = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			printf("2nd GNL error\n");
			return (-1);
		}
		strings = ft_split(line, ' ');
		if (strings == NULL)
		{
			printf("split error\n");
			free(line);
			return (-1);
		}
		if (ft_strcmp(strings[1], "jmp") == 0)
		{
			i = ft_atoi(strings[0]);
			swap_strings(inst[i].type, nop);
		}
		else if (ft_strcmp(strings[1], "nop") == 0)
		{
			i = ft_atoi(strings[0]);
			swap_strings(inst[i].type, jmp);
		}
		int acc = execute_instructions(inst);
		free(line);
		if (acc != -1)
		{
			printf("swapped %s with %s at index inst[%d]", inst[i].type, jmp, i);
			printf("Success with acc: %d\n", acc);
			ft_free_split(strings);
			return (acc);
		}
		else if (ft_strcmp(strings[1], "nop") == 0)
			swap_strings(inst[i].type, jmp);
		else if (ft_strcmp(strings[1], "jmp") == 0)
			swap_strings(inst[i].type, nop);
		ft_free_split(strings);
		cnt++;
	}
	printf("rip\n");
	return (acc);
}

int	print_instruction(t_instructions *inst)
{
	int	i;
	int	acc;
	int	total;

	i = 0;
	acc = 0;
	total = 0;
	while (i < 642)
	{
		total++;
		if (inst[i].executed == 1)
			return (-1);
		printf("%d %s\n", i, inst[i].type);
		inst[i].executed++;
		if (ft_strcmp(inst[i].type, "acc") == 0)
			acc += inst[i].value;
		else if (ft_strcmp(inst[i].type, "jmp") == 0)
		{
			i += inst[i].value;
			continue ;
		}
		i++;
	}
	printf("exited successfully\n");
	return (acc);
}

int	read_in_data(const char *pathname)
{
	char	*line;
	int		fd;
	int		ret;
	t_instructions	inst[642];
	int		i;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("open error\n");
		return (-1);
	}
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			printf("GNL error");
			// if anyone was allocated, free here
			return (-1);
		}
		//do stuff with line
		if (ret != 0)
		{
			if (extract_instruction(inst + i, line) == -1)
			{
				free_instructions(inst, i);
				free(line);
				printf("instruction extraction error\n");
				return (-1);
			}
			i++;
		}
		free(line);
	}
	// int acc = print_instruction(inst);
	int acc = brute_force(inst);
	free_instructions(inst, i);
	printf("acc: %d\n", acc);
	close(fd);
	return (0);
}

int	main(void)
{
	read_in_data("input.txt");
	return (0);
}
