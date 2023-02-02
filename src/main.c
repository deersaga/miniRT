/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:25:21 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/02 11:35:19 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

FLOAT	degrees_to_radians(FLOAT degrees)
{
	return (degrees * M_PI / 180);
}

t_point	ray_at(const t_ray *r, FLOAT t)
{
	t_point	p;

	p = vec_add(r->origin, vec_scalar_mul(t, r->direction));
	return (p);
}

t_ray	get_ray(t_camera *camera, int x, int y)
{
	t_vec	ey;
	t_vec	dx;
	t_vec	dy;
	t_vec	pm;
	t_vec	ray_dir;
	FLOAT	u;
	FLOAT	v;
	FLOAT	screen_distance;

	ey = vec_new(0, 1, 0);
	screen_distance = SCREEN_WIDTH * ASPECT_RATIO / (2 * (FLOAT)tan(degrees_to_radians(camera->hfov) / 2));
	camera->look_at_direction = vec_unit(camera->look_at_direction);
	dx = vec_cross(ey, camera->look_at_direction);
	dy = vec_cross(camera->look_at_direction, dx);
	u = map(x, 0, WIDTH - 1, -1, 1) * ASPECT_RATIO;
	v = map(y, 0, HEIGHT - 1, 1, -1);
	pm = vec_add(camera->eye_position,
			vec_scalar_mul(screen_distance, camera->look_at_direction));
	ray_dir = vec_sub(
				vec_add(pm,
				vec_add(vec_scalar_mul(u, dx), vec_scalar_mul(v, dy))),
				camera->eye_position);
	ray_dir = vec_unit(ray_dir);
	return ((t_ray){.origin = camera->eye_position, .direction = ray_dir});
}

void	draw_image(t_screen *screen, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;

	(void)scene;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_ray(&scene->camera, x, y);
			color = ray_trace(&ray, scene);
			put_pixel(screen->img, x, y, get_mlx_color(color));
			x++;
		}
		y++;
	}
}

void	print_element(t_element *head)
{
	while (head)
	{
		printf("type %d color [%f %f %f]\n", head->element_type, head->color.x, head->color.y, head->color.z);
		head = head->next;
	}
}

int	main(int argc, const char *argv[])
{
	t_screen	screen;
	t_scene		scene;
	t_element	*parsed_result;

	parsed_result = parse(argc, argv);
	scene.sphere.next = NULL;
	translate(&scene, parsed_result);
	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(screen.mlx_ptr, WIDTH, HEIGHT, "screen");
	screen.img = init_img(screen.mlx_ptr, WIDTH, HEIGHT);
	draw_image(&screen, &scene);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr,
		screen.img->ptr, 0, 0);
	mlx_closebutton_hook(screen.win_ptr, close_window, &screen);
	mlx_loop(screen.mlx_ptr);
	return (0);
}
