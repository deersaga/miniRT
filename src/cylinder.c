/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:11:30 by susami            #+#    #+#             */
/*   Updated: 2023/02/05 12:24:24 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static bool	cylinder_hit_internal(const t_cylinder *self, t_hit_record *rec, FLOAT t, const t_ray *r)
{
	t_vec	intersection;
	t_vec	h = self->orientation;
	t_vec	q;
	t_vec	cq;
	FLOAT	cq_len;

	intersection = ray_at(r, t);
	cq_len = vec_dot(vec_sub(intersection, self->center), h);
	if (cq_len < 0 || cq_len > self->height)
		return (false);
	rec->hittable_ptr = self;
	rec->t = t;
	rec->p = intersection;
	cq = vec_scalar_mul(cq_len, h);
	q = vec_add(self->center, cq);
	set_face_normal(
		rec,
		r,
		vec_scalar_div(
			vec_sub(rec->p, q),
			self->radius
			)
		);
	return (true);
}

bool	cylinder_hit(const t_cylinder *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec)
{
	t_vec	v = r->direction;
	t_vec	w = vec_sub(r->origin ,self->center);
	t_vec	h = self->orientation;
	FLOAT	vhdot = vec_dot(v, h);
	FLOAT	whdot = vec_dot(w, h);
	FLOAT	a = vec_length_squared(v) - vhdot * vhdot;
	FLOAT	half_b = vec_dot(v, w) - vhdot * whdot;
	FLOAT	c = vec_length_squared(w) - whdot * whdot - self->radius * self->radius;
	FLOAT	discriminant = half_b * half_b - a * c;
	FLOAT	root, temp;

	if (discriminant > 0)
	{
		root = sqrt(discriminant);
		temp = (-half_b - root) / a;
		if (temp < t_max && temp > t_min)
		{
			if (cylinder_hit_internal(self, rec, temp, r))
				return (true);
		}
		temp = (-half_b + root) / a;
		if (temp < t_max && temp > t_min)
		{
			if (cylinder_hit_internal(self, rec, temp, r))
				return (true);
		}
	}
	return (false);
}