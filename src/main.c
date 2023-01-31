/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:25:21 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 15:20:04 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec.h"
#include "mlx.h"
#include <stdlib.h>

void	*init_img(void	*mlx_ptr, int width, int height)
{
	t_img	*img;

	img = calloc(1, sizeof(*img));
	if (img == NULL)
		exit(1);
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

int	main(void)
{
	t_screen	screen;

	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(screen.mlx_ptr, WIDTH, HEIGHT, "screen");
	screen.img = init_img(screen.mlx_ptr, WIDTH, HEIGHT);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr,
		screen.img->ptr, 0, 0);
	mlx_loop(screen.mlx_ptr);
	return (0);
}
