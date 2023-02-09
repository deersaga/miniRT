/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validate_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:52:04 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 03:07:23 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"
#include "minirt.h"

void	expect_not_too_big(FLOAT val)
{
	if (val > BORDER)
		fatal_error("expect_not_too_big", "value is too big");
}

void	expect_not_too_big_or_small_vec(t_vec *v)
{
	const FLOAT	boarder = BORDER;

	if (v->x > boarder || v->y > boarder || v->z > boarder)
		fatal_error("expect_not_too_big_or_small_vec", "value is too big");
	if (v->x < -boarder || v->y < -boarder || v->z < -boarder)
		fatal_error("expect_not_too_big_or_small_vec", "value is too small");
}

void	expect_once(t_element_type type)
{
	static bool	has_seen_ambient = false;
	static bool	has_seen_light = false;
	static bool	has_seen_camera = false;

	if (type == E_AMBIENT_LIGHTNING)
	{
		if (has_seen_ambient)
			fatal_error("expect_once", "A can only be declared once.");
		has_seen_ambient = true;
	}
	else if (type == E_LIGHT)
	{
		if (has_seen_light)
			fatal_error("expect_once", "L can only be declared once.");
		has_seen_light = true;
	}
	else if (type == E_CAMERA)
	{
		if (has_seen_camera)
			fatal_error("expect_once", "C can only be declared once.");
		has_seen_camera = true;
	}
	else
		fatal_error("expect_once", "Unexpected type");
}
