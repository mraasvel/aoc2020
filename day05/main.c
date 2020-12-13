/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 13:10:20 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/05 13:46:23 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

typedef struct	s_seat
{
	int	taken;
	int	row;
	int	column;
}				t_seat;

int	ft_int_pow(int a, int pwr)
{
	int	base;
	if (pwr == 0)
		return (1);
	else if (pwr == 1)
		return (a);
	base = 1;
	while (pwr > 0)
	{
		base *= a;
		pwr--;
	}
	return (base);
}

void	replace_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'F' || line[i] == 'L')
			line[i] = '0';
		else
			line[i] = '1';
		i++;
	}
}
// pow 2 1 0, i = 7, 8, 9 9 - i
int	generate_seat_value(t_seat *seats, char *line)
{
	int	i;
	int	row;
	int	column;
	int	seat_id;

	i = 0;
	row = 0;
	column = 0;
	replace_chars(line);
	while (i < 7)
	{
		if (line[i] == '1')
			row += ft_int_pow(2, 6 - i);
		i++;
	}
	while (i < 10)
	{
		if (line[i] == '1')
			column += ft_int_pow(2, 9 - i);
		i++;
	}
	seat_id = row * 8 + column;
	seats[seat_id].taken = 1;
	seats[seat_id].column = column;
	seats[seat_id].row = row;
	return (0);
}

int	find_free_seats(t_seat *seats)
{
	int	i;
	int	max;
	int	count;

	count = 0;
	i = 0;
	max = 0;
	while (i < 1024)
	{
		if (seats[i].taken == 0)
		{
			if (i != 0 && i != 1023)
			{
				if (seats[i + 1].taken == 1 && seats[i - 1].taken == 1)
				{
					printf("%d\n", i);
					count++;
				}
			}
		}
		i++;
	}
	printf("count: %d\n", count);
	return (count);
}

int	read_in_file(char *pathname)
{
	int		fd;
	int		ret;
	char	*line;
	t_seat	seats[1024];

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		printf("fd error\n");
		return (-1);
	}
	ret = 1;
	for (int i = 0; i < 1024; i++)
	{
		seats[i].taken = 0;
	}
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			printf("GNL error\n");
			return (-1);
		}
		generate_seat_value(seats, line);
		free(line);
	}
		find_free_seats(seats);
	return (0);
}

int	main(void)
{
	read_in_file("input.txt");
	return (0);
}
