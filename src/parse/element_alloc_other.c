/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_alloc_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:52:28 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 02:49:29 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "element.h"

t_element	*cylinder_element_alloc(t_point center, t_vec orientation,
		t_range r_and_h, t_color color)
{
	t_element	*self;

	self = ft_calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("cylinder_element_alloc", "calloc error");
	self->element_type = E_CYLINDER;
	self->cy_center = center;
	self->cy_orientation = orientation;
	self->cy_diameter = r_and_h.min;
	self->cy_height = r_and_h.max;
	self->color = color;
	return (self);
}

t_element	*plane_element_alloc(t_point point, t_vec normal, t_color color)
{
	t_element	*self;

	self = ft_calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("plane_element_alloc", "calloc error");
	self->element_type = E_PLANE;
	self->pl_point = point;
	self->pl_normal = normal;
	self->color = color;
	return (self);
}

t_element	*sphere_element_alloc(t_vec center, FLOAT diameter, t_color color)
{
	t_element	*self;

	self = ft_calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("sphere_element_alloc", "calloc error");
	self->element_type = E_SPHERE;
	self->sp_center = center;
	self->sp_diameter = diameter;
	self->color = color;
	return (self);
}
