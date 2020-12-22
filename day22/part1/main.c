/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 08:29:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 10:56:55 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day22.h"

void	print_list(t_deck *start)
{
	printf("[");
	while(start != NULL)
	{
		printf("%d", start->card);
		if (start->next != NULL)
			printf(" ");
		start = start->next;
	}
	printf("]\n");
}

int	read_file(int fd, t_deck **p1, t_deck **p2)
{
	char	*line;
	int		ret;

	ret = 1;
	ft_getline(fd, &line);
	free(line);
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (*line == '\0')
			break ;
		append_element(p1, ft_atoi(line));
		free(line);
	}
	free(line);
	ret = 1;
	ft_getline(fd, &line);
	free(line);
	while (ret > 0)
	{
		ret = ft_getline(fd, &line);
		if (ret == -1)
			return (-1);
		if (*line == '\0')
			break ;
		append_element(p2, ft_atoi(line));
		free(line);
	}
	if (ret == 0)
		free(line);
	return (0);
}

int	main(void)
{
	int		fd;
	t_deck	*p1;
	t_deck	*p2;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (-1);
	p1 = NULL;
	p2 = NULL;
	read_file(fd, &p1, &p2);
	close(fd);
	printf("Initial Decks:\nPlayer 1: ");
	print_list(p1);
	printf("Player 2: ");
	print_list(p2);
	// play_game_p1(copy_deck(p1), copy_deck(p2));
	play_game_p2(copy_deck(p1), copy_deck(p2), 0);
	free_list(&p1);
	free_list(&p2);
	return (0);
}
