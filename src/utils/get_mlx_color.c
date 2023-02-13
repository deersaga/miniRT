/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mlx_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:00:29 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/13 12:19:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec.h"

int	get_mlx_color(t_color c)
{
	int	p;

	p = 0;
	p += (int)(clamp(c.x, range_new(0, 1)) * 255.9999) << 16;
	p += (int)(clamp(c.y, range_new(0, 1)) * 255.9999) << 8;
	p += (int)(clamp(c.z, range_new(0, 1)) * 255.9999);
	return (p);
}
