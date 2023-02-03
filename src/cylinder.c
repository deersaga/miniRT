/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:11:30 by susami            #+#    #+#             */
/*   Updated: 2023/02/03 12:36:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	cylinder_set_hit_record(const t_cylinder *self, t_hit_record *rec, FLOAT t, const t_ray *r)
{
	t_vec	q;

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

bool	cylinder_hit(const t_cylinder *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec)
{
	t_vec	v = r->direction;
	t_vec	w = vec_sub(r->origin ,self->center);
	t_vec	h = self->orientation;
	FLOAT	vhdot = vec_dot(v, h);
	FLOAT	whdot = vec_dot(w, h);
	FLOAT	a = vec_length_squared(v) - vhdot * vhdot;
	FLOAT	b = 2 * (vec_dot(v, w) - vhdot * whdot);
	FLOAT	c = vec_length_squared(w) - whdot * whdot - self->radius * self->radius;
	FLOAT	discriminant = b * b - 4 * a * c;
	FLOAT	root, half_b = b / 2, temp;

	if (discriminant > 0)
	{
		root = sqrt(discriminant);
		temp = (-half_b - root) / a;
		if (temp < t_max && temp > t_min)
		{
			cylinder_set_hit_record(self, rec, temp, r);
			return (true);
		}
		temp = (-half_b + root) / a;
		if (temp < t_max && temp > t_min)
		{
			cylinder_set_hit_record(self, rec, temp, r);
			return (true);
		}
	}
	return (false);
}
