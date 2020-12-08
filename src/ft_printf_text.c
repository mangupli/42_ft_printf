/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:05:58 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 19:28:07 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		print_no_type(char c, t_spec *format)
{
	int len;

	len = 1;
	if (!(format->flags & MINUS))
	{
		if ((format->flags & ZERO) && (format->flags & WIDTH)
			&& format->width)
		{
			putnchar('0', format->width - len);
			len = format->width;
		}
		else
			len = print_spaces(len, format->width);
	}
	ft_putchar(c);
	if ((format->flags & MINUS))
		len = print_spaces(len, format->width);
	return (len);
}

int		print_spaces(int len, int width)
{
	while ((width - len) > 0)
	{
		ft_putchar(32);
		len++;
	}
	return (len);
}

int		print_string(va_list arg, t_spec *format)
{
	int		len;
	char	*str;
	char	*cpy;
	int		zeros;
	int		spaces;

	if (!(str = va_arg(arg, char *)))
		str = ft_strdup("(null)");
	if (format->flags & PRECISION)
	{
		if (!(cpy = (char *)malloc(sizeof(char) * (format->precision + 1))))
			return (PRINT_FAILURE);
		cpy = ft_strncpy(cpy, str, format->precision);
		str = cpy;
	}
	len = ft_strlen(str);
	spaces = count_spaces(format, &len);
	zeros = (format->flags & ZERO) ? count_zeros(format, &len, 0) : 0;
	!(format->flags & MINUS) ? putnchar(' ', spaces) : 0;
	putnchar('0', zeros);
	ft_putstr(str);
	(format->flags & PRECISION) ? free(cpy) : 0;
	(format->flags & MINUS) ? putnchar(' ', spaces) : 0;
	return (len);
}

int		print_character(va_list arg, t_spec *format)
{
	int		len;
	char	c;

	c = va_arg(arg, int);
	len = 1;
	if (!(format->flags & MINUS))
		len = print_spaces(len, format->width);
	ft_putchar(c);
	if ((format->flags & MINUS))
		len = print_spaces(len, format->width);
	return (len);
}
