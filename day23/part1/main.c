/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/23 08:21:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/23 10:07:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day23.h"

t_cups	*create_list(void)
{
	t_cups	*labels;
	int		i;

	i = 0;
	labels = NULL;
	while (LABELS[i] != 0)
	{
		list_append(&labels, LABELS[i] - '0');
		i++;
	}
	i++;
	while (i <= MILLION)
	{
		list_append(&labels, i);
		i++;
	}
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

t_cups	*find_destination(t_cups *cups, int current_cup)
{
	t_cups	*finder;

	while (1)
	{
		current_cup--;
		if (current_cup < MIN)
			current_cup = MAX;
		finder = cups;
		while (finder != NULL)
		{
			if (finder->cup == current_cup)
				return (finder);
			finder = finder->next;
		}
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
	destination = find_destination(*cups, current_cup->cup);
	list_insert(cups, destination, pick_up);
}

t_cups	*find_value(t_cups *cups, int value)
{
	while (cups != NULL)
	{
		if (cups->cup == value)
			return (cups);
		cups = cups->next;
	}
	return (cups);
}

void	print_part2_result(t_cups *cups, t_cups *one)
{
	t_cups	*get;
	size_t	result;

	get = one->next;
	if (get == NULL)
		get = cups;
	result = get->cup;
	get = get->next;
	if (get == NULL)
		get = cups;
	result *= get->cup;
	printf("Part 2: %lu\n", result);
}

int	part1(t_cups **cups)
{
	t_cups	*current_cup;
	int		i;

	current_cup = *cups;
	i = 0;
	while (i < MOVE_COUNT)
	{
		do_move(cups, current_cup);
		current_cup = current_cup->next;
		if (current_cup == NULL)
			current_cup = *cups;
		i++;
	}
	current_cup = find_value(*cups, 1);
	// print_cups(*cups);
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
