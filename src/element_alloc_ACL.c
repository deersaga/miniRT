/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_alloc_ACL.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:52:28 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 21:13:33 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "parse.h"
#include "minirt.h"
#include "parse.h"

t_element	*light_element_alloc(t_vec p, FLOAT ratio, t_color color)
{
	t_element	*self;

	self = ft_calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_LIGHT;
	self->light_point = p;
	self->light_brightness_ratio = ratio;
	self->color = color;
	return (self);
}

t_element	*camera_element_alloc(t_vec p, t_vec dir, FLOAT hfov)
{
	t_element	*self;

	self = ft_calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_CAMERA;
	self->view_point = p;
	self->orientation = dir;
	self->hfov = hfov;
	return (self);
}

t_element	*ambient_element_alloc(FLOAT ratio, t_color color)
{
	t_element	*self;

	self = ft_calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_AMBIENT_LIGHTNING;
	self->ambient_lightning_ratio = ratio;
	self->color = color;
	return (self);
}
