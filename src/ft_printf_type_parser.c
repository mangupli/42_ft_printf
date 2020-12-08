/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:16:25 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 17:35:34 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	type_position(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (PRINT_FAILURE);
}

static int	get_type(char c, t_spec *format, char *str)
{
	int		type;
	int		*types_array;

	types_array = (int *)ft_calloc(TYPES_LEN, sizeof(int));
	if (types_array == NULL)
		return (-1);
	types_array[C] = C_BIT;
	types_array[S] = S_BIT;
	types_array[P] = P_BIT;
	types_array[D] = D_BIT;
	types_array[I] = I_BIT;
	types_array[U] = U_BIT;
	types_array[LOWER_X] = LOWER_X_BIT;
	types_array[UPPER_X] = UPPER_X_BIT;
	type = type_position(c, str);
	if (type != PRINT_FAILURE)
		format->flags |= types_array[type];
	free(types_array);
	return (type);
}

int			parse_format(char **string, t_spec *format, va_list arg)
{
	int		type;
	int		check_format;
	char	*types_string;

	if (!(types_string = (char *)malloc(sizeof(char) * TYPES_LEN)))
		return (-1);
	types_string = ft_strncpy(types_string, TYPES, TYPES_LEN);
	type = PRINT_FAILURE;
	while (**string)
	{
		if ((type_position(**string, types_string) != PRINT_FAILURE) &&
			((type = get_type(**string, format, types_string)) > -1))
			break ;
		check_format = get_format(string, format, arg);
		if (check_format == 0)
			break ;
		if (check_format == -1)
			return (PRINT_FAILURE);
	}
	free(types_string);
	return (type);
}
