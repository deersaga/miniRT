/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:08:08 by susami            #+#    #+#             */
/*   Updated: 2023/02/06 12:00:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

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

// TODO: Linux, x86 macos, macs in school
#define ESCAPE 65307

int	key_handler(int keycode, t_screen *screen)
{
	(void)screen;
	printf("key pressed: %d\n", keycode);
	if (keycode == ESCAPE)
		close_window(screen);
	return (0);
}
