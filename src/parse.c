#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "minirt.h"
#include "get_next_line.h"


t_shape	get_shapes(void)
{
	t_shape		head;
	t_shape		*shape;
	
	return ((t_shape){SPHERE, NULL, NULL, vec_new(3, 0, 25), 1.0})
	//head.next = NULL;
	// shape = &head;
	// {
	// 	shape = shape->next = shape_new(SPHERE);
	// 	shape->center = vec_new(3, 0, 25);
	// 	shape->radius = 1.0;
	// 	shape->material = get_default_material(fcolor_new(0.69, 0, 0));
	// }
	// {
	// 	shape = shape->next = shape_new(SPHERE);
	// 	shape->center = vec_new(2, 0, 20);
	// 	shape->radius = 1.0;
	// 	shape->material = get_default_material(fcolor_new(0, 0.69, 0));
	// }
	// {
	// 	shape = shape->next = shape_new(SPHERE);
	// 	shape->center = vec_new(1, 0, 15);
	// 	shape->radius = 1.0;
	// 	shape->material = get_default_material(fcolor_new(0, 0, 0.69));
	// }
	// {
	// 	shape = shape->next = shape_new(SPHERE);
	// 	shape->center = vec_new(0, 0, 10);
	// 	shape->radius = 1.0;
	// 	shape->material = get_default_material(fcolor_new(0, 0.69, 0.69));
	// }
	// /*
	// {
	// 	shape = shape->next = shape_new(SPHERE);
	// 	shape->center = vec_new(-1, 0, 5);
	// 	shape->radius = 1.0;
	// 	shape->material = get_default_material(fcolor_new(0.69, 0, 0.69));
	// }
	// */
	// {
	// 	shape = shape->next = shape_new(CYLINDER);
	// 	shape->center = vec_new(-1, 0, 5);
	// 	shape->radius = 1.0;
	// 	shape->orientation = vec_new(-3.0, 4.0, -10.0);
	// 	vec_normalize(shape->orientation);
	// 	shape->height = 1.0;
	// 	shape->material = get_default_material(fcolor_new(0.69, 0, 0.69));
	// }
	// {
	// 	shape = shape->next = shape_new(PLANE);
	// 	shape->center = vec_new(0, -1, 0);
	// 	shape->normal = vec_new(0, 1, 0);
	// 	shape->material = get_default_material(fcolor_new(0.69, 0.69, 0.69));
	// }
	//return (head.next);
}

t_light_source	get_light_sources(void)
{
	// t_light_source	head;
	// t_light_source	*ls;

	return ((t_light_source){POINT, new_color(1, 1, 1), NULL, vec_new(0, 5, 0), vec_new(0, 0, 0)});
	// head.next = NULL;
	// ls = &head;
	// {
	// 	ls = ls->next = {POINT, new_color(1, 1, 1), NULL, vec_new(0, 5, 0), vec_new(0, 0, 0)};
	// 	ls->position = vec_new(-5, 5, -5);
	// 	ls->intencity = fcolor_new(0.5, 0.5, 0.5);
	// }
	// return (head.next);
}

t_scene	*get_scene(void)
{
	t_scene	*scene;

	scene = calloc(1, sizeof(*scene));
	scene->shapes = get_shapes();
	scene->light_sources = get_light_sources();
	scene->eye_position = vec_new(0, 0, -5);
	scene->look_at = vec_new(0, 0, 0);
	scene->screen_distance = 5.0;
	return (scene);
}

t_scene	parse(int argc, const char *argv[])
{
	t_scene	*scene;
	int	fd;
	char	*tail;
	char	*line;

	//scene = (t_scene){};
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
	scene = get_scene();
	return (*scene);
}


		// if (!strcmp(line, "A 0.2 255,255,255\n"))
		// 	;
		// else if (!strcmp(line, "C -50.0,0,20 0,0,1 70\n"))
		// 	;
		// else if (!strcmp(line, "sp 0.0,0.0,20.6 12.6 10,0,255\n"))
		// 	;
		// else
		// 	fatal_error("parse", line);
