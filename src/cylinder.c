/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:11:30 by susami            #+#    #+#             */
/*   Updated: 2023/02/08 20:58:02 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static bool	cylinder_hit_internal(const t_cylinder *self, t_hit_record *rec,
		FLOAT t, const t_ray *r)
{
	const t_vec	h = self->orientation;
	t_vec		intersection;
	t_vec		q;
	FLOAT		cq_len;

	intersection = ray_at(r, t);
	cq_len = vec_dot(vec_sub(intersection, self->center), h);
	if (cq_len < 0 || cq_len > self->height)
		return (false);
	rec->hittable_ptr = self;
	rec->t = t;
	rec->p = intersection;
	q = vec_add(self->center, vec_scalar_mul(cq_len, h));
	set_face_normal(rec, r, vec_scalar_div(vec_sub(rec->p, q), self->radius));
	return (true);
}

static void	calc_quadratic_eq(
		t_quad_eq *f_eq, const t_sphere *self, const t_ray *r)
{
	const t_vec	v = r->direction;
	const t_vec	w = vec_sub(r->origin, self->center);
	const t_vec	h = self->orientation;
	const FLOAT	vhdot = vec_dot(v, h);
	const FLOAT	whdot = vec_dot(w, h);

	f_eq->a = vec_length_squared(v) - vhdot * vhdot;
	f_eq->hb = vec_dot(v, w) - vhdot * whdot;
	f_eq->c = vec_length_squared(w) - whdot * whdot
		- self->radius * self->radius;
	f_eq->discriminant = f_eq->hb * f_eq->hb - f_eq->a * f_eq->c;
	f_eq->root = sqrt(f_eq->discriminant);
}

bool	cylinder_hit(const t_cylinder *self, const t_ray *r,
			t_range tr, t_hit_record *rec)
{
	t_quad_eq	f_eq;
	FLOAT		temp;

	calc_quadratic_eq(&f_eq, self, r);
	if (f_eq.discriminant > 0)
	{
		temp = (-f_eq.hb - f_eq.root) / f_eq.a;
		if (temp < tr.max && temp > tr.min)
		{
			if (cylinder_hit_internal(self, rec, temp, r))
				return (true);
		}
		temp = (-f_eq.hb + f_eq.root) / f_eq.a;
		if (temp < tr.max && temp > tr.min)
		{
			if (cylinder_hit_internal(self, rec, temp, r))
				return (true);
		}
	}
	return (false);
}
