/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:23:48 by susami            #+#    #+#             */
/*   Updated: 2023/02/07 11:12:39 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_hit_record *self, const t_ray *r,
		t_vec outward_normal)
{
	self->front_face = vec_dot(r->direction, outward_normal) < 0;
	if (self->front_face)
		self->normal = outward_normal;
	else
		self->normal = vec_scalar_mul(-1.0, outward_normal);
}

bool	hit(const t_hittable *self, const t_ray *r, FLOAT t_min,
		FLOAT t_max, t_hit_record *rec)
{
	if (self->type == H_SPHERE)
		return (sphere_hit(self, r, t_min, t_max, rec));
	else if (self->type == H_LIST)
		return (hittable_list_hit(self, r, t_min, t_max, rec));
	else if (self->type == H_PLANE)
		return (plane_hit(self, r, t_min, t_max, rec));
	else if (self->type == H_CYLINDER)
		return (cylinder_hit(self, r, t_min, t_max, rec));
	else
		fatal_error("hit", "Unexpected hittable type");
}
