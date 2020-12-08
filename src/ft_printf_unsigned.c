/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:12:19 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 17:36:10 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*get_nbr_hex(char *hex_symbols, char *number_hex, uintmax_t num)
{
	int hex_ptr;
	int i;

	i = !num ? 1 : 0;
	while (num)
	{
		hex_ptr = num % 16;
		number_hex[i++] = hex_symbols[hex_ptr];
		num /= 16;
	}
	number_hex[i] = '\0';
	number_hex = ft_strrev(number_hex);
	return (number_hex);
}

int		count_hex_len(uintmax_t num)
{
	int len;

	len = (!num) ? 1 : 0;
	while (num)
	{
		len++;
		num >>= 4;
	}
	return (len);
}

char	*get_nbr_unsigned(int *len, uintmax_t n, int base)
{
	uintmax_t	tmp;
	int			i;
	char		*result;

	*len = ((!n) ? 1 : 0);
	tmp = n;
	while (tmp)
	{
		tmp /= base;
		(*len)++;
	}
	if (!(result = (char *)malloc(sizeof(char) * (*len + 1))))
		return (NULL);
	*result = '0';
	i = ((!n) ? 1 : 0);
	while (n)
	{
		tmp = n % base;
		n /= base;
		result[i++] = tmp + '0';
	}
	result[i] = '\0';
	result = ft_strrev(result);
	return (result);
}

int		print_pointer(uintmax_t n, t_spec *format,
						char *(*convert)(int *, uintmax_t))
{
	int			zeros;
	int			spaces;
	int			len;
	char		*number;

	number = convert(&len, n);
	if ((format->flags & PRECISION && !(format->precision) && !n))
		len--;
	len += 2;
	zeros = count_zeros(format, &len, 0);
	spaces = count_spaces(format, &len);
	(!(format->flags & MINUS)) ? putnchar(' ', spaces) : 0;
	ft_putstr("0x");
	putnchar('0', zeros);
	if (!(format->flags & PRECISION && !(format->precision) && !n))
		ft_putstr(number);
	(format->flags & MINUS) ? putnchar(' ', spaces) : 0;
	free(number);
	return (len);
}

int		print_unsigned(uintmax_t n, t_spec *format,
						char *(*convert)(int *, uintmax_t))
{
	int			zeros;
	int			spaces;
	int			len;
	char		*number;

	number = convert(&len, n);
	format->flags & UPPER_X_BIT ? number = ft_str_to_upper(number) : 0;
	zeros = count_zeros(format, &len, 0);
	spaces = count_spaces(format, &len);
	(!(format->flags & MINUS)) ? putnchar(' ', spaces) : 0;
	putnchar('0', zeros);
	if (!(format->flags & PRECISION && !(format->precision) && !n))
		ft_putstr(number);
	else if ((format->flags & WIDTH) && format->width)
		ft_putchar(' ');
	else
		len--;
	(format->flags & MINUS) ? putnchar(' ', spaces) : 0;
	free(number);
	return (len);
}
