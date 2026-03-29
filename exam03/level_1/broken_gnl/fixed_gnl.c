/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 18:03:56 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/29 18:27:45 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	int	i = 0;

	// Added s[i] to prevent segfaults
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{

	// Fixed memcpy implementation
	size_t i = 0;

	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;

	// Added NULL check
	if (!s)
		return (0);

	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	size_t	i = n - 1;
	while (i > 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;

	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return (NULL);

		// Mark index one of buffer as NULL
		b[0] = '\0';

		int	read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);

		// Check for EOF
		if (read_ret == 0)
			break ;

		b[read_ret] = 0;

		// Search for a new line inside the buffer
		tmp = ft_strchr(b, '\n');
	}

	// If we have a new line inside the buffer
	if (tmp)
	{
		// join both the buffer content and ret content
		if (!str_append_mem(&ret, b, tmp - b + 1))
		{
			free(ret);
			return (NULL);
		}

		// Move the leftover content of tmp to the start of the buffer
		ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	}
	else
	{
		if ((!ret || !*ret))
		{
			b[0] = '\0';
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}

// int main(void)
// {
// 	int fd = open("subject.en.txt", O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// }