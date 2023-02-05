/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:37:14 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/05 12:57:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_ambient(t_scene *scene, t_element *elem)
{
	scene->ambient_intensity = vec_scalar_mul(elem->ambient_lightning_ratio / 255, elem->color);
}

void	translate_sphere(t_scene *scene, t_element *elem)
{
	t_hittable	*cur;

	cur = &scene->list;
	while (cur->next)
		cur = cur->next;
	cur->next = calloc(1, sizeof(*cur));
	cur = cur->next;
	cur->type = H_SPHERE;
	cur->ambient_factor = vec_scalar_div(elem->color, 255);
	cur->diffuse_factor = vec_scalar_div(elem->color, 255);
	cur->specular_factor = vec_scalar_div(elem->color, 255);
	cur->center = elem->sp_center;
	cur->radius = elem->sp_diameter;
	cur->shineness = 2.0;
}

void	translate_light(t_scene *scene, t_element *elem)
{
	scene->light_source.intensity = vec_scalar_div(elem->color, 255);
	scene->light_source.position = elem->light_point;
	scene->light_source.ratio = elem->light_brightness_ratio;
}

void	translate_camera(t_scene *scene, t_element *elem)
{
	scene->camera.eye_position = elem->view_point;
	scene->camera.look_at_direction = elem->orientation;
	scene->camera.hfov = elem->hfov;
}

void	translate_plane(t_scene *scene, t_element *elem)
{
	t_hittable	*cur;

	cur = &scene->list;
	while (cur->next)
		cur = cur->next;
	cur->next = calloc(1, sizeof(*cur));
	cur = cur->next;
	cur->type = H_PLANE;
	cur->ambient_factor = vec_scalar_div(elem->color, 255);
	cur->diffuse_factor = vec_scalar_div(elem->color, 255);
	cur->specular_factor = vec_scalar_div(elem->color, 255);
	cur->position = elem->pl_point;
	cur->normal = elem->pl_normal;
	cur->shineness = 2.0;
}

void	translate_cylinder(t_scene *scene, t_element *elem)
{
	t_hittable	*cur;

	cur = &scene->list;
	while (cur->next)
		cur = cur->next;
	cur->next = calloc(1, sizeof(*cur));
	cur = cur->next;
	cur->type = H_CYLINDER;
	cur->ambient_factor = vec_scalar_div(elem->color, 255);
	cur->diffuse_factor = vec_scalar_div(elem->color, 255);
	cur->specular_factor = vec_scalar_div(elem->color, 255);
	cur->center = elem->cy_center;
	cur->orientation = elem->cy_orientation;
	cur->radius = elem->cy_diameter;
	cur->height = elem->cy_height;
	cur->shineness = 2.0;
}

void	translate(t_scene *scene, t_element *head)
{
	scene->list = (t_hittable){.type = H_LIST};
	while (head)
	{
		if (head->element_type == E_AMBIENT_LIGHTNING)
			translate_ambient(scene, head);
		else if (head->element_type == E_LIGHT)
			translate_light(scene, head);
		else if (head->element_type == E_CAMERA)
			translate_camera(scene, head);
		else if (head->element_type == E_SPHERE)
			translate_sphere(scene, head);
		else if (head->element_type == E_PLANE)
			translate_plane(scene, head);
		else if (head->element_type == E_CYLINDER)
			translate_cylinder(scene, head);
		head = head->next;
	}
}
