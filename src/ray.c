/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:49:05 by susami            #+#    #+#             */
/*   Updated: 2023/02/13 13:49:26 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	ray_at(const t_ray *r, FLOAT t)
{
	t_point	p;

	p = vec_add(r->origin, vec_scalar_mul(t, r->direction));
	return (p);
}
