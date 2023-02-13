/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:37:27 by susami            #+#    #+#             */
/*   Updated: 2023/02/13 12:18:54 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

t_vec	vec_new(FLOAT x, FLOAT y, FLOAT z)
{
	return ((t_vec){.x = x, .y = y, .z = z});
}

t_point	point_new(FLOAT x, FLOAT y, FLOAT z)
{
	return ((t_point){.x = x, .y = y, .z = z});
}

t_color	color_new(FLOAT x, FLOAT y, FLOAT z)
{
	return ((t_color){.x = x, .y = y, .z = z});
}
