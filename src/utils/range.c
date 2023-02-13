/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:37:48 by susami            #+#    #+#             */
/*   Updated: 2023/02/13 13:37:49 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
