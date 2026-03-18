/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:23:55 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/18 19:14:19 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	*get_arr(int size)
{
	int	*arr;

	arr = malloc(size * sizeof(int));
	if (!arr)
		return (NULL);
	return (arr);
}

void	fill_arr(int *arr, const char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		arr[i] = atoi(argv[i]);
		i++;
	}
}

void	print_solution(int *seen, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d", seen[i]);
		if (i++ < size - 1)
			printf(" ");
	}
	printf("\n");
}

void	solve(int *set, int size, int *seen, int seen_size, int pos, int sum)
{
	int	i = pos;

	if (sum == set[0])
		print_solution(seen, seen_size);

	while (i < size)
	{
		seen[seen_size] = set[i];
		solve(set, size, seen, seen_size + 1, i + 1, sum + set[i]);
		i++;
	}
}

int	main(int argc, const char **argv)
{
	int	*set;
	int	*seen;
	int	size;
	int	i;

	// We check if we have at least one arg
	if (argc < 2)
		return (1);

	size = argc - 1;

	// Malloc both arrays and return in case of NULL
	set = get_arr(size);
	seen = get_arr(size);
	if (!set || !seen)
		return (1);

	// Fill the set array with argv values
	fill_arr(set, argv + 1);

	solve(set, size, seen, 0, 1, 0);
}
