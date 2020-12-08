/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:54:24 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 17:35:05 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	get_precision(char *str, t_spec *format, va_list arg)
{
	int		len;
	char	*num;

	len = 0;
	if (str[len] == '.')
	{
		len++;
		if (str[len] == '*')
		{
			format->precision = va_arg(arg, int);
			len++;
		}
		else
		{
			while (ft_isdigit(str[len]))
				len++;
			if (!(num = ft_substr(str, 1, len)))
				return (-1);
			format->precision = ft_atoi(num);
			free(num);
		}
	}
	return (len);
}

static int	get_width(char *str, t_spec *format, va_list arg)
{
	int		len;
	char	*num;

	len = 0;
	if (str[0] == '*')
	{
		format->width = va_arg(arg, int);
		if (format->width < 0)
		{
			format->width *= -1;
			format->flags |= MINUS;
		}
		len++;
	}
	else
	{
		while (ft_isdigit(str[len]))
			len++;
		if (!(num = ft_substr(str, 0, len)))
			return (PRINT_FAILURE);
		format->width = ft_atoi(num);
		free(num);
	}
	return (len);
}

static int	get_flags(char fl, t_spec *format)
{
	fl == '-' ? format->flags |= MINUS : 0;
	fl == '0' ? format->flags |= ZERO : 0;
	return (fl == '0' || fl == '-');
}

int			get_format(char **string, t_spec *format, va_list arg)
{
	char	*begin;
	int		format_len;

	begin = *string;
	while (get_flags(**string, format))
		(*string)++;
	if ((format_len = get_width(*string, format, arg)) > -1)
	{
		format->flags |= WIDTH;
		*string += format_len;
	}
	else
		return (PRINT_FAILURE);
	while ((format_len = get_precision(*string, format, arg)))
	{
		if (format_len == -1)
			return (PRINT_FAILURE);
		if (format->precision >= 0)
			format->flags |= PRECISION;
		(*string) += format_len;
	}
	return (*string > begin);
}
