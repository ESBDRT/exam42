/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:02:56 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/12 19:05:42 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"

void	filter(char *stash, const char *arg)
{
	size_t i, j, k, len;

	len = strlen(arg);
	i = 0;
	while (stash[i])
	{
		j = 0;
		while (arg[j] && arg[j] == stash[i + j])
			j++;
		if (j == len)
		{
			k = 0;
			while (k < len)
			{
				write(1, "*", 1);
				k++;
			}
			i += len;
		}
		else
			write(1, &stash[i++], 1);
	}
}

int	main(int argc, const char **argv)
{
	char	buffer[BUFFER_SIZE] = {0};
	char	*stash = NULL;
	int		bytes;
	size_t	total_read;

	if ((argc != 2) || (!argv[1][0]))
		return (1);

	while ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 1)
	{
		total_read += bytes;
		stash = realloc(stash, total_read + 1);
		if (!stash)
			return (perror("Error :"), 1);
		memmove(stash + total_read - bytes, buffer, bytes);
	}
	if (bytes < 0)
		return (perror("Error :"), 1);
	filter(stash, argv[1]);
	return (0);
}
