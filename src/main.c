/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:25:21 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/01 11:55:50 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>

void	*init_img(void	*mlx_ptr, int width, int height)
{
	t_img	*img;

	img = calloc(1, sizeof(*img));
	if (img == NULL)
		fatal_error("init img", NULL);
	img->ptr = mlx_new_image(mlx_ptr, width, height);
	if (img->ptr == NULL)
		exit(1);
	img->mlx_ptr = mlx_ptr;
	img->data = mlx_get_data_addr(img->ptr,
			&img->bits_per_pixel,
			&img->bytes_per_line,
			&img->endian);
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	return (img);
}

// This hook is triggered by key DOWN, not by key UP.
void	mlx_keydown_hook(void *win_ptr, int (*handler)(), void *param)
{
	mlx_hook(win_ptr, KeyPress, KeyPressMask, handler, param);
}

// This hook is triggered by pressing window's x button.
void	mlx_closebutton_hook(void *win_ptr, int (*handler)(), void *param)
{
	mlx_hook(win_ptr, ClientMessage, StructureNotifyMask, handler, param);
}

/*
 * Disable hooks before destroy, to avoid calling hooks
 * after some images/windows/displays are destroyed.
*/
int	close_window(t_screen *s)
{
	mlx_closebutton_hook(s->win_ptr, NULL, NULL);
	mlx_loop_hook(s->mlx_ptr, NULL, NULL);
	mlx_destroy_image(s->mlx_ptr, s->img->ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_display(s->mlx_ptr);
	free(s->img);
	exit(0);
}

static char	get_n_th_byte(int x, int n)
{
	const int	size = 8;
	const int	index = n * size;
	int			mask;
	char		ret;

	mask = ((n << size) - 1) << index;
	ret = (char)((x & mask) >> index);
	return (ret);
}

// Update img data
// If endian is little endian, write from head,
// Else write from tail.
void	put_pixel(const t_img *img, int x, int y, int mlx_color)
{
	int	x_color;
	int	head;
	int	i;
	int	index;

	x_color = mlx_get_color_value(img->mlx_ptr, mlx_color);
	head = (x * img->bytes_per_pixel) + (y * img->bytes_per_line);
	i = 0;
	while (i < img->bytes_per_pixel)
	{
		if (img->endian == 0)
		{
			index = head + i;
		}
		else
		{
			index = head + img->bytes_per_pixel - 1 - i;
		}
		img->data[index] = get_n_th_byte(x_color, i);
		i++;
	}
}

FLOAT	degrees_to_radians(FLOAT degrees)
{
	return (degrees * M_PI / 180);
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

t_color	ray_trace(const t_ray *r, t_scene *scene)
{
	t_vec	unit_direction;
	FLOAT	t;

	(void)scene;
	unit_direction = vec_unit(r->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vec_add(vec_scalar_mul((1.0 - t), color_new(1.0, 1.0, 1.0)), vec_scalar_mul(t, color_new(0.5, 0.7, 1.0))));
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

int	main(int argc, const char *argv[])
{
	t_screen	screen;
	t_scene		scene;

	(void)scene;
	scene = parse(argc, argv);
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
