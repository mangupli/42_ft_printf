/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_signed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:17:01 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 19:28:09 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	putnchar(char c, int len)
{
	while (len)
	{
		ft_putchar(c);
		len--;
	}
}

int		count_spaces(t_spec *format, int *len)
{
	int ret;

	ret = 0;
	if (format->flags & WIDTH && format->width > *len && \
	(!(format->flags & ZERO) || format->flags & MINUS || \
	format->flags & PRECISION))
	{
		ret = format->width - *len;
		*len += ret;
	}
	return (ret);
}

int		count_zeros(t_spec *format, int *len, int sign)
{
	int ret;

	ret = 0;
	if (format->flags & S_BIT && format->flags & ZERO && format->width > *len)
	{
		ret = format->width - *len;
		*len += ret;
		return (ret);
	}
	if ((format->flags & PRECISION) && \
				(format->precision > (*len - sign)))
	{
		ret = format->precision - *len + sign;
		*len += ret;
	}
	if ((format->flags & WIDTH) && (format->flags & ZERO) && \
		!(format->flags & PRECISION) && !(format->flags & MINUS) && \
		format->width > *len)
	{
		ret = format->width - *len;
		*len += ret;
	}
	return (ret);
}

int		count_nbr_len(int n)
{
	int len;

	if (n == 0)
		return (1);
	len = (n < 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/*
**	First, count for the number of digits (sign also if number < 0),
**	then count for the number of zeroes (they shoul be counted first,
**	because the sign matters for them) and spaces (what left after
**	zeroes). There is an ugly condition  before actually printing
**	the number. It's for the case if precision == 0 and number == 0.
**	Real printf prints nothing in this case.
*/

int		print_signed(va_list arg, t_spec *format)
{
	int			len;
	intmax_t	n;
	int			zeros;
	int			spaces;

	n = va_arg(arg, int);
	len = count_nbr_len(n);
	zeros = count_zeros(format, &len, (n < 0));
	spaces = count_spaces(format, &len);
	!(format->flags & MINUS) ? putnchar(' ', spaces) : 0;
	n < 0 ? ft_putchar('-') : 0;
	putnchar('0', zeros);
	if (!(!n && format->flags & PRECISION && !format->precision))
		ft_putunbr((n < 0) ? (-n) : (n));
	else if ((format->flags & WIDTH) && format->width)
		ft_putchar(' ');
	else
		len--;
	(format->flags & MINUS) ? putnchar(' ', spaces) : 0;
	return (len);
}
