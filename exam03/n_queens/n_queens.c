/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:58:04 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/16 18:28:21 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_result(char **board)
{
	int	i;
	int	j;

	i = 0;
	while (board[i])
	{
		j = 0;
		while (board[i][j])
		{
			if (board[i][j] == 'Q')
				fprintf(stdout, "%d", j);
			j++;
		}
		if (board[i++])
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
	return ;
}

static char	**init_board(int size)
{
	char	**board;
	int		i;
	int		j;

	board = malloc((size + 1) * sizeof(char *));
	if (!board)
		return (NULL);
	i = 0;
	while (i < size)
	{
		board[i] = malloc((size + 1) * sizeof(char));
		if (!board[i])
			return (NULL);
		j = 0;
		while (j < size)
		{
			board[i][j] = '.';
			j++;
		}
		board[i][j] = '\0';
		i++;
	}
	board[i] = NULL;
	i = 0;
	return (board);
}

int	is_column_empty(char **board, int y, int x)
{
	while (y != -1)
	{
		if (board[y][x] == 'Q')
			return (0);
		y--;
	}
	return (1);
}

int	is_diagonal_empty(char **board, int y, int x, int size)
{
	int	tmp_x;
	int	tmp_y;

	tmp_y = y;
	tmp_x = x;
	while (tmp_y > -1 && tmp_x > -1)
	{
		if (board[tmp_y--][tmp_x--] == 'Q')
			return (0);
	}
	tmp_y = y;
	tmp_x = x;
	while (tmp_y > -1 && tmp_x < size)
	{
		if (board[tmp_y--][tmp_x++] == 'Q')
			return (0);
	}
	return (1);
}

int	solve(char **board, int size, int y)
{
	int	x;

	if (y == size)
		return (print_result(board), 0);
	x = 0;
	while (x < size)
	{
		if (is_column_empty(board, y, x) && is_diagonal_empty(board, y, x,
				size))
		{
			board[y][x] = 'Q';
			solve(board, size, y + 1);
			board[y][x] = '.';
		}
		x++;
	}
	return (0);
}

int	main(int argc, const char **argv)
{
	char	**board;
	int		size;
	int		i;
	int		j;

	if (argc != 2)
		return (1);
	size = atoi(argv[1]);
	board = init_board(size);
	if (!board)
		return (1);
	solve(board, size, 0);
}
