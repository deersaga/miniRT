/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:59:15 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/07 11:14:35 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

FLOAT	clamp(FLOAT v, FLOAT vmin, FLOAT vmax)
{
	if (v > vmax)
		return (vmax);
	else if (v < vmin)
		return (vmin);
	else
		return (v);
}

// map(v, vmin, vmax, tmin, tmax)
// = tmin + (tmax - tmin) x clamp(v, vmin, vmax) / (vmax - vmin)
FLOAT	map(FLOAT v, FLOAT vmin, FLOAT vmax, FLOAT tmin, FLOAT tmax)
{
	return (tmin + (tmax - tmin) * clamp(v, vmin, vmax) / (vmax - vmin));
}
