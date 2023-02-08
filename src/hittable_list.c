/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:23:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/08 21:32:51 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hittable_list_hit(
		const t_hittable *head, const t_ray *r, t_range tr, t_hit_record *rec)
{
	bool			hit_any;
	FLOAT			closest_t;
	t_hit_record	temp_rec;

	hit_any = false;
	closest_t = tr.max;
	head = head->next;
	while (head)
	{
		if (hit(head, r, range_new(tr.min, closest_t), &temp_rec))
		{
			hit_any = true;
			closest_t = temp_rec.t;
			*rec = temp_rec;
		}
		head = head->next;
	}
	return (hit_any);
}
