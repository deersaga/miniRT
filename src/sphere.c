/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:11:58 by susami            #+#    #+#             */
/*   Updated: 2023/02/09 20:20:18 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static void	sphere_set_hit_record(const t_sphere *self, t_hit_record *rec,
		FLOAT t, const t_ray *r)
{
	rec->hittable_ptr = self;
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

static void	calc_quadratic_eq(
		t_quad_eq *f_eq, const t_sphere *self, const t_ray *r)
{
	const t_vec	oc = vec_sub(r->origin, self->center);

	f_eq->a = vec_length_squared(r->direction);
	f_eq->half_b = vec_dot(oc, r->direction);
	f_eq->c = vec_length_squared(oc) - self->radius * self->radius;
	f_eq->discriminant = f_eq->half_b * f_eq->half_b - f_eq->a * f_eq->c;
	f_eq->root = sqrt(f_eq->discriminant);
}

bool	sphere_hit(const t_sphere *self, const t_ray *r,
			t_range tr, t_hit_record *rec)
{
	t_quad_eq	f_eq;
	FLOAT		temp;

	calc_quadratic_eq(&f_eq, self, r);
	if (f_eq.discriminant > 0)
	{
		temp = (-f_eq.half_b - f_eq.root) / f_eq.a;
		if (temp < tr.max && temp > tr.min)
		{
			sphere_set_hit_record(self, rec, temp, r);
			return (true);
		}
		temp = (-f_eq.half_b + f_eq.root) / f_eq.a;
		if (temp < tr.max && temp > tr.min)
		{
			sphere_set_hit_record(self, rec, temp, r);
			return (true);
		}
	}
	return (false);
}
