/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:37:14 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 21:32:53 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_ambient(t_scene *scene, t_element *elem);
void	translate_light(t_scene *scene, t_element *elem);
void	translate_camera(t_scene *scene, t_element *elem);

void	set_material_info(t_hittable *obj, t_color color)
{
	obj->ambient_factor = vec_scalar_mul(0.01 / 255, color);
	obj->diffuse_factor = vec_scalar_mul(0.69 / 255, color);
	obj->specular_factor = vec_scalar_mul(0.3 / 255, color);
	obj->shineness = 8.0;
}

void	translate_sphere(t_scene *scene, t_element *elem)
{
	t_hittable	*cur;

	cur = &scene->list;
	while (cur->next)
		cur = cur->next;
	cur->next = ft_calloc(1, sizeof(*cur));
	cur = cur->next;
	cur->type = H_SPHERE;
	cur->center = elem->sp_center;
	cur->radius = elem->sp_diameter;
	set_material_info(cur, elem->color);
}

void	translate_plane(t_scene *scene, t_element *elem)
{
	t_hittable	*cur;

	cur = &scene->list;
	while (cur->next)
		cur = cur->next;
	cur->next = ft_calloc(1, sizeof(*cur));
	cur = cur->next;
	cur->type = H_PLANE;
	cur->position = elem->pl_point;
	cur->normal = elem->pl_normal;
	set_material_info(cur, elem->color);
}

void	translate_cylinder(t_scene *scene, t_element *elem)
{
	t_hittable	*cur;

	cur = &scene->list;
	while (cur->next)
		cur = cur->next;
	cur->next = ft_calloc(1, sizeof(*cur));
	cur = cur->next;
	cur->type = H_CYLINDER;
	cur->center = elem->cy_center;
	cur->orientation = elem->cy_orientation;
	cur->radius = elem->cy_diameter;
	cur->height = elem->cy_height;
	set_material_info(cur, elem->color);
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
