/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 15:49:36 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/08 19:15:09 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"

int	main(int argc, const char **argv)
{
	size_t	bytes = 0;
	size_t	total_read = 0;
	size_t	 i, j, k;
	size_t 	arg_len;
	char	buffer[BUFFER_SIZE] = {0};
	char	*stash = NULL;
	char	*arg = NULL;

	if ((argc != 2) || (argv[1][0] == '\0'))
		return (1);

	while ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 1)
	{
		total_read += bytes;
		stash = realloc(stash, total_read + 1);
		if (!stash)
			return (perror("realloc"), 1);
		memmove(stash + total_read - bytes, buffer, bytes);
	}

	if (bytes < 0)
		return (free(stash), perror("read"), 1);

	arg = (char *)argv[1];
	arg_len = strlen(arg);
	i = 0;
	while (stash[i])
	{
		j = 0;
		while (arg[j] && arg[j] == stash[i + j])
			j++;
		if (j == arg_len)
		{
			k = 0;
			while (k < arg_len)
			{
				write(1, "*", 1);
				k++;
			}
			i += arg_len;
		}
		else
			write(1, &stash[i++], 1);
	}
}
