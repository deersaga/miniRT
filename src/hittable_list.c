/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:23:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/02 12:24:01 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hittable_list_hit(const t_hittable *head, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec)
{
	bool			hit_any;
	FLOAT			closest_t;
	t_hit_record	temp_rec;

	hit_any = false;
	closest_t = t_max;
	head = head->next;
	while (head)
	{
		if (hit(head, r, t_min, closest_t, &temp_rec))
		{
			hit_any = true;
			closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		head = head->next;
	}
	return (hit_any);
}
