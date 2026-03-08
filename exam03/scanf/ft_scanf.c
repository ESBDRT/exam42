/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouet <edrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:13:25 by edrouet           #+#    #+#             */
/*   Updated: 2026/03/08 15:28:55 by edrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>

int	match_space(FILE *f)
{
	int	c;
	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			break ;
		}
	}
	if (c == EOF)
		return (-1);
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	ch;

	ch = fgetc(f);
	if (ch == c)
		return (1);
	ungetc(ch, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	int		c;
	char	*arg;

	arg = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
	{
		ungetc(c, f);
		return (0);
	}
	*arg = c;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	char	c;
	int		sign;
	int		result;
	int		found;
	int		*arg;

	sign = 1;
	c = fgetc(f);
	found = 0;
	arg = va_arg(ap, int *);
	if (c == '-')
	{
		sign = -1;
		c = fgetc(f);
	}
	result = 0;
	while (c != EOF && isdigit(c))
	{
		result = result * 10 + (c - '0');
		c = fgetc(f);
		found = 1;
	}
	if (c == EOF)
		ungetc(c, f);
	if (found)
	{
		*arg = result * sign;
		return (1);
	}
	return (0);
}

int	scan_string(FILE *f, va_list ap)
{
	int		c;
	int		i;
	char	*arg;

	arg = va_arg(ap, char *);
	i = 0;
	c = fgetc(f);
	if (c == EOF)
	{
		ungetc(c, f);
		return (0);
	}
	while (c != EOF)
	{
		if ((isspace(c)))
		{
			ungetc(c, f);
			break ;
		}
		arg[i] = c;
		i++;
		c = fgetc(f);
	}
	arg[i] = '\0';
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
	case 'c':
		return (scan_char(f, ap));
	case 'd':
		match_space(f);
		return (scan_int(f, ap));
	case 's':
		match_space(f);
		return (scan_string(f, ap));
	case EOF:
		return (-1);
	default:
		return (-1);
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	c;

	nconv = 0;
	c = fgetc(f);
	if (c == EOF)
		return (EOF);
	ungetc(c, f);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break ;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break ;
		}
		else if (match_char(f, *format) != 1)
			break ;
		format++;
	}
	if (ferror(f))
		return (EOF);
	return (nconv);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

int	main(void)
{
	const char	*format;
	int			age;
	char		name[20];
	int			result;

	format = "age %d nom %s";
	result = ft_scanf(format, &age, name);
	printf("%d\n", result);
	return (0);
}
