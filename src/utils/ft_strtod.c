/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:45 by susami            #+#    #+#             */
/*   Updated: 2023/03/20 22:25:47 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static char	*convert_to_d(const char *str, double *ret)
{
	double	dec;
	bool	dot;

	dot = false;
	dec = 1.0 / 10;
	while (ft_isdigit(*str) || *str == '.')
	{
		if (dot)
		{
			if (*str == '.')
				break ;
			*ret += dec * (*str - '0');
			dec /= 10;
		}
		else
		{
			if (*str == '.')
				dot = true;
			else if (ft_isdigit(*str))
				*ret = *ret * 10 + (*str - '0');
		}
		str++;
	}
	return ((char *)str);
}

double	ft_strtod(const char *str, char **rest)
{
	double	ret;
	double	sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '.' && !ft_isdigit(*(str + 1)))
		return (0);
	ret = 0;
	*rest = convert_to_d(str, &ret);
	return (ret * sign);
}
