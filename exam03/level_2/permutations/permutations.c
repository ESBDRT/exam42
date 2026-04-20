/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:04:41 by edrouet           #+#    #+#             */
/*   Updated: 2026/04/20 16:20:55 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}

void	ft_swap(char *str, int idx1, int idx2)
{
	char	tmp;

	tmp = str[idx1];
	str[idx1] = str[idx2];
	str[idx2] = tmp;
}

void	ft_sort_str(char *str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] > str[j])
				ft_swap(str, i, j);
			j++;
		}
		i++;
	}
}

void	permutations(char *str, int len, int idx)
{
	int	i;

	i = idx;
	// Print the permutation
	if (idx == len)
	{
		ft_putstr(str);
		return ;
	}
	ft_sort_str(str + idx, len - idx);
	while (i < len)
	{
		ft_swap(str, i, idx);
		// Recursive call
		permutations(str, len, idx + 1);
		// Backtrack
		ft_swap(str, i, idx);
		i++;
	}
}

int	main(int argc, const char **argv)
{
	int len;
	char *str;

	if ((argc < 2) || (!argv[1]))
		return (1);

	str = (char *)argv[1];
	len = ft_strlen(str);

	// Handle len 1
	if (len == 1)
		return (ft_putstr(str), 0);

	// Handle len 2
	else if (len == 2)
	{
		ft_putstr(str);
		ft_swap(str, 0, 1);
		ft_putstr(str);
		return (0);
	}

	else
	{
		ft_sort_str(str, len);
		permutations(str, len, 0);
	}

	return (0);
}