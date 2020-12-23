/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/23 08:21:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/23 11:57:47 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day23.h"

t_cups	*jump_table[MILLION];

t_cups	*create_list(void)
{
	t_cups	*labels;
	t_cups	*current;
	int		i;

	i = 0;
	labels = list_create(LABELS[i] - '0');
	jump_table[LABELS[i] - '0'] = labels;
	i = 1;
	current = labels;
	while (LABELS[i] != 0)
	{
		current->next = list_create(LABELS[i] - '0');
		jump_table[LABELS[i] - '0'] = current->next;
		current = current->next;
		i++;
	}
	i++;
	while (i <= MILLION)
	{
		current->next = list_create(i);
		jump_table[i] = current->next;
		current = current->next;
		i++;
	}
	printf("lalala\n");
	return (labels);
}

void	print_cups(t_cups *start)
{
	printf("List:");
	while (start != NULL)
	{
		printf(" %d", start->cup);
		start = start->next;
	}
	printf("\n");
}

t_cups	*find_destination(t_cups *cups, t_cups *pick_up, int current_cup)
{
	t_cups	*finder;

	while (1)
	{
		current_cup--;
		if (current_cup < MIN)
			current_cup = MAX;
		finder = pick_up;
		while (finder != NULL)
		{
			if (finder->cup == current_cup)
				break ;
			finder = finder->next;
		}
		if (finder == NULL)
			return (jump_table[current_cup]);
	}
	return (NULL);
}

void	print_move(t_cups *cups, int current_cup, t_cups *destination, t_cups *picked_up)
{
	printf("Current cup: %d\n", current_cup);
	printf("Pick up: ");
	print_cups(picked_up);
	printf("Destination: %d\n", destination->cup);
	print_cups(cups);
}

int	do_move(t_cups **cups, t_cups *current_cup)
{
	t_cups	*pick_up;
	t_cups	*destination;

	pick_up = list_extract(cups, current_cup, 3);
	destination = find_destination(*cups, pick_up, current_cup->cup);
	list_insert(cups, destination, pick_up);
}

t_cups	*find_value(t_cups *cups, int value)
{
	return (jump_table[value]);
}

void	print_part2_result(t_cups *cups, t_cups *one)
{
	t_cups	*get;
	size_t	result;

	printf("one: %d\n", one->cup);
	get = one->next;
	if (get == NULL)
		get = cups;
	printf("Result1: %d\n", get->cup);
	result = get->cup;
	printf("Number one: %d\n", get->cup);
	get = get->next;
	if (get == NULL)
		get = cups;
	printf("Result2: %d\n", get->cup);
	result *= get->cup;
	printf("Number two: %d\n", get->cup);
	printf("Part 2: %lu\n", result);
}

void	print_until_one_plus_two(t_cups *cups)
{
	t_cups	*finder;
	int		found;

	finder = cups;
	found = 0;
	int i = 0;
	while (i < 3 && finder != NULL)
	{
		if (found == 1)
			i++;
		printf(" %d", finder->cup);
		if (finder->cup == 1)
			found = 1;
		finder = finder->next;
	}
	printf("\n");
}

int	part1(t_cups **cups)
{
	t_cups	*current_cup;
	int		i;

	current_cup = *cups;
	i = 0;
	while (i < MOVE_COUNT)
	{
		if (i % 1000 == 0)
			printf("move: %d\n", i);
		do_move(cups, current_cup);
		current_cup = current_cup->next;
		if (current_cup == NULL)
			current_cup = *cups;
		i++;
	}
	current_cup = find_value(*cups, 1);
	// print_cups(*cups);
	// print_until_one_plus_two(*cups);
	print_part2_result(*cups, current_cup);
	return (0);
}

int	main(void)
{
	t_cups	*cups;

	cups = create_list();
	part1(&cups);
	list_clear(&cups);
	return (0);
}
