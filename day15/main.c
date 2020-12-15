/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 08:27:02 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/15 09:18:22 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "header.h"
#include "libft.h"

/* allocating tons of memory to avoid making an effective data structure */
#define TABLE_SIZE_1 10000
#define TABLE_SIZE_2 30000000
/* main input array */
#define SIZE 7
const int input[7] = {0,13,16,17,1,10,6};

// #define SIZE 3
// const int input[SIZE] = {1,3,2}; // 2020th = 1
// #define SIZE 3
// const int input[SIZE] = {2,1,3}; // 2020th = 10
// #define SIZE 3
// const int input[SIZE] = {0,3,6}; // 2020th = 10

typedef enum	e_checks
{
	success,
	not_found,
	found
}				t_checks;

typedef struct	s_num
{
	int	found;
	int	index;
}				t_num;

void	print_vector(t_intvect *vector)
{
	for (size_t i = 0; i < vector->nmemb; i++)
	{
		printf("%lu: %d\n", i + 1, vector->table[i]);
	}
}

int	interpret_input_part1(t_intvect *vector)
{
	t_num	table[TABLE_SIZE_1];
	size_t	i;

	for (i = 0; i < TABLE_SIZE_1; i++)
		table[i].found = not_found;
	for (i = 0; i < SIZE - 1; i++)
	{
		table[vector->table[i]].found = found;
		table[vector->table[i]].index = i;
	}
	for (; i < 2020 - 1; i++)
	{
		if (table[vector->table[i]].found == not_found)
		{
			table[vector->table[i]].found = found;
			table[vector->table[i]].index = i;
			intvect_pushback(0, vector);
		}
		else
		{
			intvect_pushback(i - table[vector->table[i]].index, vector);
			table[vector->table[i]].index = i;
		}
	}
	printf("number: %d\n", vector->table[2020 - 1]);
	return (0);
}

int	interpret_input_part2(t_intvect *vector)
{
	t_num	*table;
	size_t	i;

	table = (t_num*)malloc(TABLE_SIZE_2 * sizeof(t_num));
	if (table == NULL)
		return (-1);
	for (i = 0; i < TABLE_SIZE_2; i++)
		table[i].found = not_found;
	for (i = 0; i < SIZE - 1; i++)
	{
		table[vector->table[i]].found = found;
		table[vector->table[i]].index = i;
	}
	for (; i < 30000000 - 1; i++)
	{
		if (table[vector->table[i]].found == not_found)
		{
			table[vector->table[i]].found = found;
			table[vector->table[i]].index = i;
			intvect_pushback(0, vector);
		}
		else
		{
			intvect_pushback(i - table[vector->table[i]].index, vector);
			table[vector->table[i]].index = i;
		}
	}
	printf("number: %d\n", vector->table[30000000 - 1]);
	free(table);
	return (0);
}


int	main(void)
{
	t_intvect	*vector;

	vector = intvect_init(2);
	for (size_t i = 0; i < SIZE; i++)
	{
		intvect_pushback(input[i], vector);
	}
	interpret_input_part1(vector);
	// interpret_input_part2(vector);
	intvect_free(vector);
	return (0);
}
