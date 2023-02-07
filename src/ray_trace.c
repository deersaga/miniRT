/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:43:37 by susami            #+#    #+#             */
/*   Updated: 2023/02/07 11:16:24 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

#define C_EPSILON 0.0001

t_color	diffuse_light(t_hit_record *rec, t_lighting *lighting)
{
	t_color	color;
	FLOAT	nldot;

	nldot = vec_dot(lighting->direction, rec->normal);
	if (nldot <= 0)
		return (color_new(0, 0, 0));
	color = vec_mul(lighting->intensity, rec->hittable_ptr->diffuse_factor);
	color = vec_mul(color, color_new(nldot, nldot, nldot));
	return (color);
}

t_color	specular_light(const t_ray *ray, t_hit_record *rec,
		t_lighting *lighting)
{
	FLOAT		nldot;
	FLOAT		vrdot;
	FLOAT		vrdot_pow_alpha;
	t_vec		reflec;
	t_vec		b;
	t_vec		view;
	t_color		ki;

	nldot = vec_dot(lighting->direction, rec->normal);
	b = vec_scalar_mul(nldot * 2, rec->normal);
	reflec = vec_sub(b, lighting->direction);
	view = vec_scalar_mul(-1, ray->direction);
	view = vec_unit(view);
	vrdot = vec_dot(view, reflec);
	if (nldot <= 0 || vrdot <= 0)
		return (color_new(0, 0, 0));
	vrdot_pow_alpha = pow(vrdot, rec->hittable_ptr->shineness);
	ki = vec_mul(rec->hittable_ptr->specular_factor, lighting->intensity);
	return (vec_mul(
			ki,
			color_new(vrdot_pow_alpha, vrdot_pow_alpha, vrdot_pow_alpha)));
}

t_lighting	lighting_at(const t_light_source *self, t_vec pos)
{
	t_lighting	lighting;

	lighting.direction = vec_sub(self->position, pos);
	lighting.distance = vec_length(lighting.direction);
	lighting.direction = vec_unit(lighting.direction);
	lighting.intensity = self->intensity;
	return (lighting);
}

bool	is_shadow(const t_hit_record *rec, const t_lighting *l,
		const t_scene *scene)
{
	t_ray			shadow_ray;
	t_hit_record	temp_rec;

	shadow_ray = (t_ray){.direction = l->direction, .origin = rec->p};
	return (hit(&scene->list, &shadow_ray, C_EPSILON, l->distance, &temp_rec));
}

t_color	ray_trace(const t_ray *r, t_scene *scene)
{
	t_vec			unit_direction;
	FLOAT			t;
	t_hit_record	rec;
	t_color			ret_color;
	t_lighting		lighting;

	if (hit(&scene->list, r, C_EPSILON, INFINITY, &rec))
	{
		ret_color = vec_mul(scene->ambient_intensity,
				rec.hittable_ptr->ambient_factor);
		lighting = lighting_at(&scene->light_source, rec.p);
		if (is_shadow(&rec, &lighting, scene))
			return (ret_color);
		ret_color = vec_add(ret_color, diffuse_light(&rec, &lighting));
		ret_color = vec_add(ret_color, specular_light(r, &rec, &lighting));
		return (ret_color);
	}
	unit_direction = vec_unit(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vec_add(
			vec_scalar_mul((1.0 - t), color_new(1.0, 1.0, 1.0)),
			vec_scalar_mul(t, color_new(0.5, 0.7, 1.0))));
}
