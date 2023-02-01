/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/01 18:13:49 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "minirt.h"

t_element	*sphere_element_alloc(t_vec center, FLOAT diameter, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = SPHERE;
	self->center = center;
	self->diameter = diameter;
	self->color = color;
	return (self);
}

t_element	*light_element_alloc(t_vec p, FLOAT ratio, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = LIGHT;
	self->light_point = p;
	self->light_brightness_ratio = ratio;
	self->color = color;
	return (self);
}

t_element	*camera_element_alloc(t_vec p, t_vec dir, FLOAT hfov)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = CAMERA;
	self->view_point = p;
	self->orientation_vec = dir;
	self->hfov = hfov;
	return (self);
}

t_element	*ambient_element_alloc(FLOAT ratio, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = AMBIENT_LIGHTNING;
	self->ambient_lightning_ratio = ratio;
	self->color = color;
	return (self);
}

void	element_add(t_element *head, t_element *elem)
{
	while (head->next)
	{
		head = head->next;
	}
	head->next = elem;
}

t_element	*parse(int argc, const char *argv[])
{
	t_element	head;
	int			fd;
	char		*tail;

	errno = 0;
	if (argc != 2)
		fatal_error("parse", "[Usage]: ./miniRT config_file");
	tail = strrchr(argv[1], '.');
	if (tail == NULL || strcmp(tail, ".rt"))
		fatal_error("parse", "extension must be .rt");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fatal_error("parse", NULL);
	close(fd);
	head.next = NULL;
	
	element_add(&head, ambient_element_alloc(0.1, color_new(255, 255, 255)));
	element_add(&head, camera_element_alloc(vec_new(-50, 0, 20), vec_new(1, 0, 0), 70));
	element_add(&head, sphere_element_alloc(point_new(0, 0, 20.6), 12.6, color_new(10, 0, 255)));
	element_add(&head, light_element_alloc(point_new(-40, 50.0, 20.0), 0.6 ,color_new(255, 255, 255)));

	return (head.next);
}


void	translate_ambiet(t_scene *scene, t_element *elem)
{
	scene->ambient_intensity = vec_scalar_mul(elem->ambient_lightning_ratio / 255, elem->color);
}

void	translate_sphere(t_scene *scene, t_element *elem)
{
	scene->sphere.ambient_factor = vec_scalar_div(elem->color, 255);
	scene->sphere.diffuse_factor = vec_scalar_div(elem->color, 255);
	scene->sphere.specular_factor = vec_scalar_div(elem->color, 255);
	scene->sphere.center = elem->center;
	scene->sphere.radius = elem->diameter;
	scene->sphere.shineness = 2.0;
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
	scene->camera.look_at_direction = elem->orientation_vec;
	scene->camera.hfov = elem->hfov;
}

void	translate(t_scene *scene, t_element *head)
{
	while (head)
	{
		if (head->element_type == AMBIENT_LIGHTNING)
			translate_ambiet(scene, head);
		else if (head->element_type == LIGHT)
			translate_light(scene, head);
		else if (head->element_type == CAMERA)
			translate_camera(scene, head);
		else if (head->element_type == SPHERE)
			translate_sphere(scene, head);
		head = head->next;
	}
}