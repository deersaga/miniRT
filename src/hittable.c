/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:23:48 by susami            #+#    #+#             */
/*   Updated: 2023/02/02 12:23:48 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit(const t_hittable *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec)
{
	if (self->type == H_SPHERE)
		return (sphere_hit(self, r, t_min, t_max, rec));
	else if (self->type == H_LIST)
		return (hittable_list_hit(self, r, t_min, t_max, rec));
	else
		fatal_error("hit", "Unexpected hittable type");
}
