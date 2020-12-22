/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day22.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 08:29:32 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/22 11:09:55 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY22_H
# define DAY22_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include "libft.h"
#include "libvect.h"

# define PATH "../input.txt"

typedef enum	e_returns
{
	success,
	error,
	win_p1,
	win_p2,
	state_found,
	continue_game
}				t_returns;

typedef struct	s_deck
{
	int				card;
	struct s_deck	*next;
}				t_deck;

t_deck	*create_element(int value);
int		append_element(t_deck **start, int value);
void	delete_element(t_deck **start, int value);
void	free_list(t_deck **start);
int		get_list_size(t_deck *start);
t_deck	*copy_deck(t_deck *start);
t_deck	*copy_n_elements(t_deck *start, int n);
int		compare_decks(t_deck *p1, t_deck *p2);

int		play_game_p1(t_deck *p1, t_deck *p2);
int		play_game_p2(t_deck *p1, t_deck *p2, int game);
void	print_list(t_deck *start);
int		get_part1_result(t_deck *winner);

#endif
