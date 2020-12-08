/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:49:07 by mspyke            #+#    #+#             */
/*   Updated: 2020/12/07 19:30:15 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_to_upper(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_islower(str[i]))
				str[i] = ft_toupper(str[i]);
			i++;
		}
	}
	return (str);
}
