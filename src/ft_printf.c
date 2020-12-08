/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:00:51 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 22:32:06 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static char	*convert_hex(int *len, uintmax_t num)
{
	char			*number_hex;
	char			*hex_symbols;

	*len = count_hex_len(num);
	if (!(number_hex = (char *)malloc(sizeof(char) * (*len) + 1)))
		return (NULL);
	*number_hex = '0';
	if (!(hex_symbols = ft_strdup("0123456789abcdef")))
		return (NULL);
	number_hex = get_nbr_hex(hex_symbols, number_hex, num);
	free(hex_symbols);
	return (number_hex);
}

static char	*convert_dec(int *len, uintmax_t num)
{
	return (get_nbr_unsigned(len, num, 10));
}

static int	formatted_print(va_list arg, t_spec *format, int t)
{
	int len;

	if (t == C)
		len = print_character(arg, format);
	else if (t == S)
		len = print_string(arg, format);
	else if ((t == D) || (t == I))
		len = print_signed(arg, format);
	else if (t == U)
		len = print_unsigned(va_arg(arg, unsigned int),
				format, &convert_dec);
	else if ((t == LOWER_X) || (t == UPPER_X))
		len = print_unsigned(va_arg(arg, unsigned int),
				format, &convert_hex);
	else if (t == P)
		len = print_pointer((uintmax_t)va_arg(arg, void *),
				format, &convert_hex);
	else if (t == PROC)
		len = print_no_type('%', format);
	else
		len = -1;
	return (len);
}

/*
** This function returns the number of characters written.
** If fails, return (-1) defined but PRINT_FAILURE macro.
*/

static int	printout(va_list arg, const char *string[])
{
	int		type;
	t_spec	format;
	int		len;

	format.flags = 0;
	format.width = 0;
	format.precision = 0;
	type = parse_format((char **)string, &format, arg);
	if (type == -1)
		return (PRINT_FAILURE);
	len = formatted_print(arg, &format, type);
	return (len);
}

int			ft_printf(const char *string, ...)
{
	va_list	argptr;
	int		count;
	int		len;

	count = 0;
	va_start(argptr, string);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			if ((len = printout(argptr, &string)) == PRINT_FAILURE)
				break ;
			count += len;
		}
		else
		{
			ft_putchar(*string);
			count++;
		}
		string++;
	}
	va_end(argptr);
	return (count);
}
