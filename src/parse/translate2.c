/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:37:14 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 03:07:35 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	scene->camera.eye_position = elem->view_point;
	scene->camera.look_at_direction = elem->orientation;
	scene->camera.hfov = elem->hfov;
}
