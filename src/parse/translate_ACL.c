/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_ACL.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:37:14 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/13 14:23:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	translate_ambient(t_scene *scene, t_element *elem)
{
	scene->ambient_intensity = vec_scalar_mul(
			elem->ambient_lightning_ratio / 255, elem->color);
}

void	translate_light(t_scene *scene, t_element *elem)
{
	scene->light_source.intensity = vec_scalar_mul(
			elem->light_brightness_ratio / 255,
			elem->color);
	scene->light_source.position = elem->light_point;
}

void	translate_camera(t_scene *scene, t_element *elem)
{
	const FLOAT	aspect_ratio = (FLOAT)WIDTH / (FLOAT)HEIGHT;
	const FLOAT	hfov_radian = degrees_to_radians(elem->hfov);
	const FLOAT	screen_distance = SCREEN_WIDTH * aspect_ratio
		/ (2 * tan(hfov_radian / 2));

	scene->camera.eye_position = elem->view_point;
	scene->camera.look_at_direction = vec_unit(elem->orientation);
	scene->camera.hfov = elem->hfov;
	scene->camera.aspect_ratio = aspect_ratio;
	scene->camera.screen_center = vec_add(
			scene->camera.eye_position,
			vec_scalar_mul(screen_distance, scene->camera.look_at_direction));
}
