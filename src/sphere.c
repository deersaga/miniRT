/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:11:58 by susami            #+#    #+#             */
/*   Updated: 2023/02/01 12:45:26 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	set_face_normal(t_hit_record *self, const t_ray *r, t_vec outward_normal)
{
	self->front_face = vec_dot(r->direction, outward_normal) < 0;
	if (self->front_face)
		self->normal = outward_normal;
	else
		self->normal = vec_scalar_mul(-1.0, outward_normal);
}

static void	sphere_set_hit_record(const t_sphere *self, t_hit_record *rec, FLOAT t, const t_ray *r)
{
	rec->sphere_ptr = self;
	rec->t = t;
	rec->p = ray_at(r, rec->t);
	set_face_normal(
		rec,
		r,
		vec_scalar_div(
			vec_sub(rec->p, self->center),
			self->radius
			)
		);
}

bool	sphere_hit(const t_sphere *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec)
{
	const t_vec	oc = vec_sub(r->origin, self->center);
	const FLOAT	a = vec_length_squared(r->direction);
	const FLOAT	half_b = vec_dot(oc, r->direction);
	const FLOAT	c = vec_length_squared(oc) - self->radius * self->radius;
	const FLOAT	discriminant = half_b * half_b - a * c;
	FLOAT		root;
	FLOAT		temp;

	if (discriminant > 0)
	{
		root = sqrt(discriminant);
		temp = (-half_b - root) / a;
		if (temp < t_max && temp > t_min)
		{
			sphere_set_hit_record(self, rec, temp, r);
			return (true);
		}
		temp = (-half_b + root) / a;
		if (temp < t_max && temp > t_min)
		{
			sphere_set_hit_record(self, rec, temp, r);
			return (true);
		}
	}
	return (false);
}
