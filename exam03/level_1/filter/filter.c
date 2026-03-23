/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:02:56 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/23 12:32:08 by edrouet          ###   ########.fr       */
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
		// Search for the substring inside the stash
		while (arg[j] && arg[j] == stash[i + j])
			j++;
		// If the substring is found, print * len times, and add len to i
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
		// Else, just write
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

	// If we don't have exactly one arg or if it's NULL, return
	if ((argc != 2) || (!argv[1][0]))
		return (1);

	// Read STDIN while it returns at least 1
	while ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
	{
		// Realloc the stash with the total number of bytes read since the start
		total_read += bytes;
		stash = realloc(stash, total_read + 1);
		// In case of a malloc error, return using perror
		if (!stash)
			return (perror("Error :"), 1);
		// Memmove buffer content at the end of stash
		memmove(stash + total_read - bytes, buffer, bytes);
	}
	// If read error, return using perror
	if (bytes < 0)
		return (perror("Error :"), 1);
	filter(stash, argv[1]);
	return (0);
}
