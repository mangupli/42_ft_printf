/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:01:18 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 19:28:58 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdint.h>

/*
** Library that allows ft_printf to have indefinite number of arguments
*/

# include <stdarg.h>

/*
** Library that allows to use malloc
*/

# include <stdlib.h>

/*
** This macro is used when there is an error
*/

# define PRINT_FAILURE (-1)

/*
** Structure that holds format specification info
*/


typedef struct		s_spec
{
	int				flags;
	int				width;
	int				precision;
}					t_spec;

/*
** The specifiers which ft_printf uses fot formatting
*/

# define TYPES "cspdiuxX%"
# define TYPES_LEN (ft_strlen(TYPES))

/*
** Order in types string
*/

# define C				(0)
# define S				(1)
# define P				(2)
# define D				(3)
# define I				(4)
# define U				(5)
# define LOWER_X		(6)
# define UPPER_X		(7)
# define PROC			(8)

/*
** Each specification of the format is represented by it's own bit
*/

# define MINUS			(FT_BIT(0))
# define ZERO			(FT_BIT(1))
# define C_BIT			(FT_BIT(2))
# define S_BIT			(FT_BIT(3))
# define P_BIT			(FT_BIT(4))
# define D_BIT			(FT_BIT(5))
# define I_BIT			(FT_BIT(6))
# define U_BIT			(FT_BIT(7))
# define LOWER_X_BIT	(FT_BIT(8))
# define UPPER_X_BIT	(FT_BIT(9))
# define WIDTH			(FT_BIT(10))
# define PRECISION		(FT_BIT(11))

/*
** Function that shifts (x) 1 bit at the left
*/

# define FT_BIT(x) (1 << (x))

/*
** Prototypes of useful functions before printing
*/

int					parse_format(char **string, t_spec *format, va_list arg);
int					get_format(char **string, t_spec *format, va_list arg);
int					count_nbr_len(int n);
int					count_zeros(t_spec *format, int *len, int sign);
int					count_spaces(t_spec *format, int *len);
char				*get_nbr_unsigned(int *len, uintmax_t n, int base);
int					count_hex_len(uintmax_t num);
char				*get_nbr_hex(char *hex_symbols, char *number_hex,
									uintmax_t num);

/*
** Prototypes of printing functions
*/

int					print_character(va_list arg, t_spec *format);
int					print_string(va_list arg, t_spec *format);
int					print_signed(va_list arg, t_spec *format);
int					print_spaces(int len, int width);
void				putnchar(char c, int len);
int					print_unsigned(uintmax_t n, t_spec *format,
								char *(*convert)(int *, uintmax_t));
int					print_pointer(uintmax_t n, t_spec *format,
								char *(*convert)(int *, uintmax_t));
int					print_hex(va_list arg, t_spec *format);
int					print_no_type(char c, t_spec *format);

/*
**ft_printf prototype
*/

int					ft_printf(const char *format, ...);

#endif
