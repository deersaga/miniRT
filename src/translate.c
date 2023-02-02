#include "minirt.h"

void	translate_ambient(t_scene *scene, t_element *elem)
{
	scene->ambient_intensity = vec_scalar_mul(elem->ambient_lightning_ratio / 255, elem->color);
}

void	translate_sphere(t_scene *scene, t_element *elem)
{
	t_sphere *head = &scene->sphere;

	while (head->next)
		head = head->next;
	head->next = calloc(1, sizeof(*head));
	head = head->next;
	head->ambient_factor = vec_scalar_div(elem->color, 255);
	head->diffuse_factor = vec_scalar_div(elem->color, 255);
	head->specular_factor = vec_scalar_div(elem->color, 255);
	head->center = elem->center;
	head->radius = elem->diameter;
	head->shineness = 2.0;
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
			translate_ambient(scene, head);
		else if (head->element_type == LIGHT)
			translate_light(scene, head);
		else if (head->element_type == CAMERA)
			translate_camera(scene, head);
		else if (head->element_type == SPHERE)
			translate_sphere(scene, head);
		head = head->next;
	}
}
