/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:05:27 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 21:31:06 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>
#include <math.h>
#include "mlx.h"

void	increment_abs_pos(t_scene *s, size_t step)
{
	t_hittable	*head;
	t_vec		step_vec;

	head = &s->list;
	step_vec = vec_new(step, step, step);
	s->camera.eye_position = vec_add(s->camera.eye_position, step_vec);
	s->light_source.position = vec_add(s->light_source.position, step_vec);
	while (head)
	{
		head->center = vec_add(head->center, step_vec);
		head->position = vec_add(head->position, step_vec);
		head = head->next;
	}
}

void	farland_test(t_scene *scene, t_screen *screen)
{
	size_t	i;
	size_t	step;
	size_t	boarder;

	step = 1;
	boarder = 10;
	i = 0;
	while (i < pow(10, 18))
	{
		increment_abs_pos(scene, step);
		draw_image(screen, scene);
		mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr,
			screen->img->ptr, 0, 0);
		if (i > boarder)
		{
			printf("borader %zu\n", boarder);
			boarder *= 10;
			step *= 9;
		}
		i += step;
	}
}
