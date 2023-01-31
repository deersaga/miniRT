/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:25:21 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 16:39:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec.h"
#include "mlx.h"
#include <stdlib.h>
#include <X11/X.h>

void	*init_img(void	*mlx_ptr, int width, int height)
{
	t_img	*img;

	img = calloc(1, sizeof(*img));
	if (img == NULL)
		fatal_error(NULL);
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

int	main(int argc, const char *argv[])
{
	t_screen	screen;
	t_scene		scene;

	(void)scene;
	scene = parse(argc, argv);
	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(screen.mlx_ptr, WIDTH, HEIGHT, "screen");
	screen.img = init_img(screen.mlx_ptr, WIDTH, HEIGHT);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr,
		screen.img->ptr, 0, 0);
	mlx_closebutton_hook(screen.win_ptr, close_window, &screen);
	mlx_loop(screen.mlx_ptr);
	return (0);
}
