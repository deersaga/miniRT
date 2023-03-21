/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:25:21 by katakagi          #+#    #+#             */
/*   Updated: 2023/03/21 16:59:36 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>

t_ray	get_ray(t_camera *camera, int x, int y)
{
	t_vec					ray_dir;
	t_display_coordinate	dc;

	dc.ey = vec_new(0, 1, 0);
	dc.dx = vec_cross(dc.ey, camera->look_at_direction);
	if (vec_length(dc.dx) == 0)
		dc.dx = vec_cross(vec_new(1, 0, 0), camera->look_at_direction);
	dc.dy = vec_cross(camera->look_at_direction, dc.dx);
	dc.u = map(x, range_new(0, WIDTH - 1), range_new(-1, 1))
		* camera->aspect_ratio;
	dc.v = map(y, range_new(0, HEIGHT - 1), range_new(1, -1));
	ray_dir = vec_sub(
			vec_add(camera->screen_center,
				vec_add(
					vec_scalar_mul(dc.u, dc.dx),
					vec_scalar_mul(dc.v, dc.dy))),
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

int	main(int argc, char *argv[])
{
	t_screen	screen;
	t_scene		scene;
	t_element	*parsed_result;

	parsed_result = parse(argc, (const char **)argv);
	translate(&scene, parsed_result);
	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(screen.mlx_ptr, WIDTH, HEIGHT, argv[1]);
	screen.img = init_img(screen.mlx_ptr, WIDTH, HEIGHT);
	draw_image(&screen, &scene);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr,
		screen.img->ptr, 0, 0);
	mlx_expose_hook(screen.win_ptr, expose_handler, &screen);
	mlx_closebutton_hook(screen.win_ptr, close_window, &screen);
	mlx_keydown_hook(screen.win_ptr, key_handler, &screen);
	mlx_loop(screen.mlx_ptr);
	return (0);
}
