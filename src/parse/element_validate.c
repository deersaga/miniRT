/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:52:04 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 03:29:55 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

void	validate_acl(t_element *elem)
{
	const t_element_type	type = elem->element_type;

	expect_once(elem->element_type);
	if (type == E_AMBIENT_LIGHTNING)
		expect_ratio(elem->ambient_lightning_ratio);
	if (type == E_CAMERA)
	{
		expect_not_too_large_vec(&elem->view_point);
		expect_not_too_large_vec(&elem->orientation);
		expect_normalized(&elem->orientation);
		expect_fov(elem->hfov);
	}
	if (type == E_LIGHT)
	{
		expect_not_too_large_vec(&elem->light_point);
		expect_ratio(elem->light_brightness_ratio);
	}
	if (type != E_CAMERA)
		expect_color(&elem->color);
}

void	validate_sphere(t_element *elem)
{
	expect_not_too_large_vec(&elem->sp_center);
	expect_non_negative(elem->sp_diameter);
	expect_not_too_big(elem->sp_diameter);
	expect_color(&elem->color);
}

void	validate_plane(t_element *elem)
{
	expect_not_too_large_vec(&elem->pl_point);
	expect_not_too_large_vec(&elem->pl_normal);
	expect_normalized(&elem->pl_normal);
	expect_color(&elem->color);
}

void	validate_cylinder(t_element *elem)
{
	expect_not_too_large_vec(&elem->cy_center);
	expect_not_too_large_vec(&elem->cy_orientation);
	expect_normalized(&elem->cy_orientation);
	expect_non_negative(elem->cy_diameter);
	expect_not_too_big(elem->cy_diameter);
	expect_non_negative(elem->cy_height);
	expect_not_too_big(elem->cy_height);
	expect_color(&elem->color);
}

// Validate orientation vector: must be normalized
// Validate FOV: must be in range [0, 180]
// Validate color: must be in range [0, 255]
// Validate light ratio: must be in range [0, 255]
void	validate_element(t_element *elem)
{
	const t_element_type	type = elem->element_type;

	if (type == E_AMBIENT_LIGHTNING || type == E_CAMERA || type == E_LIGHT)
		validate_acl(elem);
	else if (type == E_SPHERE)
		validate_sphere(elem);
	else if (type == E_PLANE)
		validate_plane(elem);
	else if (type == E_CYLINDER)
		validate_cylinder(elem);
}
