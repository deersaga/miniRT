/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:00:29 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 15:12:41 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_color	color_black(void)
{
	return ((t_color){.x = 0, .y = 0, .z = 0});
}

t_color	color_white(void)
{
	return ((t_color){.x = 1, .y = 1, .z = 1});
}

t_color	color_new(FLOAT x, FLOAT y, FLOAT z)
{
	return ((t_color){.x = x, .y = y, .z = z});
}

t_color	color_add(t_color a, t_color b)
{
	return ((t_color){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z});
}

t_color	color_sub(t_color a, t_color b)
{
	return ((t_color){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z});
}

t_color	color_mul(t_color a, t_color b)
{
	return ((t_color){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z});
}


int	get_mlx_color(t_color c)
{
	
	int	p;

	p = 0;
	p += (int)(clamp(c.x, 0, 1) * 255.9999) << 16;
	p += (int)(clamp(c.y, 0, 1) * 255.9999) << 8;
	p += (int)(clamp(c.z, 0, 1) * 255.9999);
	return (p);
}