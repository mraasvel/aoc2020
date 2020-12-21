/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:24:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/21 08:49:16 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day21.h"

t_food	foods[FOOD_SIZE];

static void print_strings(char **strings)
{
	while (*strings != NULL)
	{
		printf("%s\n", *strings);
		strings++;
	}
}

void	free_foods(void)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (foods[i].name != NULL)
	{
		j = 0;
		while (foods[i].allergens[j] != NULL)
		{
			free(foods[i].allergens[j]);
			j++;
		}
	}
}

int	add_allergen(t_food *food, char **allergens)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (allergens[i] != NULL)
	{
		j = 0;
		while (food->allergens[j] != NULL)
		{
			if (ft_strcmp(allergens[i], food->allergens[j]) == 0)
				break ;
			j++;
		}
		if (food->allergens[j] == NULL)
			food->allergens[j] = ft_strdup(allergens[i]);
		i++;
	}
}

int	add_food(char *food, char **allergens)
{
	size_t	i;

	i = 0;
	while (foods[i].name != NULL)
	{
		if (ft_strcmp(food, foods[i].name) == 0)
			add_allergen(foods + i, allergens);
		i++;
	}
	//add new food
	if (foods[i].name == NULL)
	{
		ft_strlcpy(foods[i].name, food, 100);
		add_allergen(foods + i, allergens);
	}
}

// loop until string "contains", after which the allergens will be listed
int	parse_line(char *line)
{
	char	**strings;

	strings = ft_split_set(line, " (),");
	if (strings == NULL)
		return (-1);
	print_strings(strings);
	ft_free_split(strings);
	return (0);
}

int	read_in_file(int fd)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (parse_line(line) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		break ;
	}
	return (0);
}

int	main(void)
{
	int	fd;

	fd = open (PATHNAME, O_RDONLY);
	if (fd == -1)
		return (-1);
	ft_bzero(foods, FOOD_SIZE * sizeof(t_food));
	read_in_file(fd);
	close(fd);
	free_foods();
	return (0);
}
