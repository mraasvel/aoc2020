/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 08:21:26 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/03 09:03:58 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

typedef struct	s_matrix
{
	char	**matrix;
	int		size;
	int		nmemb;
	int		line_length;
}				t_matrix;


t_matrix	*matrix_init(size_t size)
{
	t_matrix	*matrix;

	if (size == 0)
		size = 2;
	matrix = (t_matrix*)malloc(1 * sizeof(t_matrix));
	if (matrix == NULL)
		return (NULL);
	matrix->matrix = (char**)malloc(size * sizeof(char*));
	if (matrix->matrix == NULL)
	{
		free(matrix);
		return (NULL);
	}
	matrix->size = size;
	matrix->nmemb = 0;
	return (matrix);
}

int	matrix_realloc(t_matrix *matrix)
{
	char	**new_matrix;

	new_matrix = (char**)malloc((2 * matrix->size) * sizeof(char*));
	if (new_matrix == NULL)
		return (-1);
	ft_memcpy(new_matrix, matrix->matrix, matrix->nmemb * sizeof(char*));
	free(matrix->matrix);
	matrix->matrix = new_matrix;
	matrix->size = matrix->size * 2;
	return (0);
}

int	matrix_pushback(t_matrix *matrix, char *line)
{
	if (matrix->nmemb == matrix->size)
	{
		if (matrix_realloc(matrix) == -1)
			return (-1);
	}
	matrix->matrix[matrix->nmemb] = line;
	matrix->nmemb += 1;
	return (0);
}

void	*matrix_error(t_matrix *matrix)
{
	if (matrix != NULL)
	{
		while (matrix->nmemb > 0)
		{
			matrix->nmemb--;
			free(matrix->matrix[matrix->nmemb]);
		}
		free(matrix->matrix);
	}
	free(matrix);
	return (NULL);
}

t_matrix	*read_in_file(char *pathname)
{
	int			fd;
	int			ret;
	char		*line;
	t_matrix	*matrix;

	matrix = matrix_init(0);
	if (matrix == NULL || matrix->matrix == NULL)
		return (matrix_error(matrix));
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (matrix_error(matrix));
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			fprintf(stderr, "GNL error\n");
			return (matrix_error(matrix));
		}
		if (matrix_pushback(matrix, line) == -1)
		{
			fprintf(stderr, "pushback error\n");
			return (matrix_error(matrix));
		}
	}
	return (matrix);
}

int		get_tree_count(t_matrix *matrix, int rightslope, int downslope)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < matrix->nmemb)
	{
		if (matrix->matrix[i][j] == '#')
			count++;
		// printf("Count at %d %d: %d\n", i, j, count);
		j = (j + rightslope) % matrix->line_length;
		i += downslope;
	}
	return (count);
}

/*
** read in matrix of the map.
*/

int		main(void)
{
	t_matrix	*matrix;
	int			tree_count[5];
	size_t		result;

	matrix = read_in_file("input.txt");
	if (matrix == NULL || matrix->matrix == NULL)
	{
		matrix_error(matrix);
		return (0);
	}
	matrix->line_length = ft_strlen(matrix->matrix[0]);
	tree_count[0] = get_tree_count(matrix, 1, 1);
	tree_count[1] = get_tree_count(matrix, 3, 1);
	tree_count[2] = get_tree_count(matrix, 5, 1);
	tree_count[3] = get_tree_count(matrix, 7, 1);
	tree_count[4] = get_tree_count(matrix, 1, 2);
	result = tree_count[0] * tree_count[1] * tree_count[2] * tree_count[3] * tree_count[4];
	printf("result: %ld\n", result);
	matrix_error(matrix);
	return (0);
}
