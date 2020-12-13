/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 08:19:59 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/04 09:49:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

typedef struct	s_pwfields
{
	int byr;
	int iyr;
	int eyr;
	int hgt;
	int hcl;
	int ecl;
	int pid;
}				t_pwfields;

static int	ft_isrgb(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'f')
		return (1);
	return (0);
}

static void free_split(char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

int	check_byr(char *value)
{
	int	yr;

	if (ft_strlen(value) != 4)
		return (1);
	yr = ft_atoi(value);
	if (yr >= 1920 && yr <= 2002)
		return (0);
	return (1);
}

int	check_iyr(char *value)
{
	int	yr;

	if (ft_strlen(value) != 4)
		return (1);
	yr = ft_atoi(value);
	if (yr >= 2010 && yr <= 2020)
		return (0);
	return (1);
}

int	check_eyr(char *value)
{
	int	yr;

	if (ft_strlen(value) != 4)
		return (1);
	yr = ft_atoi(value);
	if (yr >= 2020 && yr <= 2030)
		return (0);
	return (1);
}

/*
** 150cm - 193cm
** 59in - 76in
*/

int	check_hgt(char *value)
{
	int	len;
	int	nbr;

	len = ft_strlen(value);
	if (len > 5 || len < 4)
		return (1);
	if (len == 5)
	{
		if (value[3] != 'c' || value[4] != 'm')
			return (1);
		nbr = ft_atoi(value);
		if (nbr >= 150 && nbr <= 193)
			return (0);
	}
	else if (len == 4)
	{
		if (value[2] != 'i' || value[3] != 'n')
			return (1);
		nbr = ft_atoi(value);
		if (nbr >= 59 && nbr <= 76)
			return (0);
	}
	return (1);
}

int	check_hcl(char *value)
{
	int	len;
	int	i;

	len = ft_strlen(value);
	if (len != 7 || value[0] != '#')
		return (1);
	i = 1;
	while (ft_isrgb(value[i]) == 1)
		i++;
	if (i == len)
		return (0);
	return (1);
}

int	check_ecl(char *value)
{
	static char *clrs[] = {
		"amb",
		"blu",
		"brn",
		"gry",
		"grn",
		"hzl",
		"oth",
		NULL
	};
	int	i;

	i = 0;
	while (clrs[i] != NULL)
	{
		if (strcmp(clrs[i], value) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_pid(char *value)
{
	int	len;
	int	i;

	i = 0;
	while (ft_isdigit(value[i]) != 0)
		i++;
	if (i == 9 && value[i] == '\0')
		return (0);
	return (1);
}

int	set_struct(t_pwfields *fields, char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		if (strcmp(strings[i], "byr") == 0)
		{
			if (check_byr(strings[i + 1]) != 0)
				return (0);
			fields->byr = 1;
		}
		else if (strcmp(strings[i], "iyr") == 0)
		{
			if (check_iyr(strings[i + 1]) != 0)
				return (0);
			fields->iyr = 1;
		}
		else if (strcmp(strings[i], "eyr") == 0)
		{
			if (check_eyr(strings[i + 1]) != 0)
				return (0);
			fields->eyr = 1;
		}
		else if (strcmp(strings[i], "hgt") == 0)
		{
			if (check_hgt(strings[i + 1]) != 0)
				return (0);
			fields->hgt = 1;
		}
		else if (strcmp(strings[i], "ecl") == 0)
		{
			if (check_ecl(strings[i + 1]) != 0)
				return (0);
			fields->ecl = 1;
		}
		else if (strcmp(strings[i], "pid") == 0)
		{
			if (check_pid(strings[i + 1]) != 0)
				return (0);
			fields->pid = 1;
		}
		else if (strcmp(strings[i], "hcl") == 0)
		{
			if (check_hcl(strings[i + 1]) != 0)
				return (0);
			fields->hcl = 1;
		}
		i += 2;
	}
	return (0);
}

int	check_struct(t_pwfields *fields)
{
	if (fields->byr == 1 && fields->iyr == 1 && fields->eyr == 1
	&& fields->hgt == 1 && fields->ecl == 1 && fields->pid == 1 && fields->hcl == 1)
		return (1);
	return (0);
}

int	print_bools(t_pwfields *fields)
{
	printf("byr: %d\niyr: %d\neyr: %d\nhgt: %d\nhcl: %d\necl: %d\npid: %d\n", fields->byr, fields->iyr, fields->eyr, fields->hgt, fields->hcl, fields->ecl, fields->pid);
}

int	read_valid_pw(char *line)
{
	char				**strings;
	static t_pwfields	*fields = 0;

	if (line[0] == '\0')
	{
		if (fields != 0)
		{
			free(fields);
			fields = 0;
		}
		return (0);
	}
	strings = ft_split_set(line, " :");
	if (strings == NULL)
	{
		fprintf(stderr, "split error\n");
		return (-1);
	}
	if (fields == 0)
	{
		fields = (t_pwfields*)malloc(1 * sizeof(t_pwfields));
		if (fields == NULL)
		{
			fprintf(stderr, "malloc error fields\n");
			free_split(strings);
			return (-1);
		}
		ft_bzero(fields, sizeof(t_pwfields));
	}
	set_struct(fields, strings);
	free_split(strings);
	print_bools(fields);
	printf("\n");
	if (check_struct(fields) == 1)
	{
		free(fields);
		fields = 0;
		return (1);
	}
	return (0);
}

int	read_in_file(char *pathname)
{
	int		fd;
	int		valid_count;
	int		ret;
	int		valid_ret;
	char	*line;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "open: FD = -1 error\n");
		return (-1);
	}
	ret = 1;
	valid_count = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			fprintf(stderr, "GNL returned -1\n");
			return (-1);
		}
		//check password validity
		valid_ret = read_valid_pw(line);
		if (valid_ret == 1)
			valid_count++;
		free(line);
		if (valid_ret == -1)
			return (-1);
	}
	return (valid_count);
}

int	main(void)
{
	int	v_count;

	v_count = read_in_file("input.txt");
	// v_count = read_in_file("test.txt");
	printf("\nvalid count: %d\n", v_count);
	return (0);
}
