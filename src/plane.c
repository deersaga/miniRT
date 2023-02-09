/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:44:50 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 20:20:16 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	plane_hit(const t_plane *self, const t_ray *r,
			t_range tr, t_hit_record *rec)
{
	t_vec	d;
	t_vec	s;
	t_vec	pc;
	FLOAT	t;
	FLOAT	dndot;

	d = r->direction;
	s = r->origin;
	pc = self->position;
	dndot = vec_dot(d, self->normal);
	if (dndot != 0)
	{
		t = vec_dot(vec_sub(pc, s), self->normal) / dndot;
		if (t > tr.min && t < tr.max)
		{
			rec->p = ray_at(r, t);
			rec->t = t;
			rec->hittable_ptr = self;
			set_face_normal(rec, r, vec_unit(self->normal));
			return (true);
		}
	}
	return (false);
}
