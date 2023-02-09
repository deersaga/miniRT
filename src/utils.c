/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:59:15 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 23:04:37 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "for_norm.h"

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

t_range	range_new(FLOAT min, FLOAT max)
{
	t_range	self;

	self.min = min;
	self.max = max;
	return (self);
}

FLOAT	clamp(FLOAT v, t_range vr)
{
	if (v > vr.max)
		return (vr.max);
	else if (v < vr.min)
		return (vr.min);
	else
		return (v);
}

// map(v, vmin, vmax, tmin, tmax)
// = tmin + (tmax - tmin) x clamp(v, vmin, vmax) / (vmax - vmin)
FLOAT	map(FLOAT v, t_range vr, t_range tr)
{
	return (tr.min + (tr.max - tr.min) * clamp(v, vr) / (vr.max - vr.min));
}
