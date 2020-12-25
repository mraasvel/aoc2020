/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/25 08:24:51 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/25 09:33:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day25.h"

size_t	get_loop_size(size_t public_key)
{
	size_t	i;
	size_t	n;

	n = 1;
	i = 0;
	while (1)
	{
		if (n == public_key)
			break ;
		n = (n * SN) % M;
		i++;
	}
	return (i);
}

size_t	get_encryption_key(size_t public_key, size_t loop_size)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 1;
	while (i < loop_size)
	{
		n = (n * public_key) % M;
		i++;
	}
	return (n);
}


size_t	test_both_keys(size_t card_pk, size_t door_pk)
{
	size_t	card_ls;
	size_t	door_ls;
	size_t	encryption_key;

	card_ls = get_loop_size(card_pk);
	door_ls = get_loop_size(door_pk);
	printf("Loopsizes: %lu %lu\n", card_ls, door_ls);
	encryption_key = get_encryption_key(door_pk, card_ls);
	if (encryption_key == get_encryption_key(card_pk, door_ls))
		return (encryption_key);
	encryption_key = get_encryption_key(card_pk, card_ls);
	if (encryption_key == get_encryption_key(door_pk, door_ls))
		return (encryption_key);
	return (error);
}

int	main(void)
{
	printf("%lu\n", test_both_keys(PK1, PK2));
	printf("%lu\n", test_both_keys(SAMPLE_PK1, SAMPLE_PK2));
	return (0);
}
