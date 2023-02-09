/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:52:04 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 21:16:19 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"
#include <float.h>
#include <unistd.h>

void	expect_ratio(FLOAT val)
{
	if (val < 0 || val > 1.0)
		fatal_error("expect_ratio", "ratio must be in range [0.0, 1.0]");
}

void	expect_fov(FLOAT val)
{
	if (val < 0 || val > 180.0)
		fatal_error("expect_fov", "FOV must be in range [0.0, 180.0]");
}

void	expect_non_negative(FLOAT val)
{
	if (val < 0)
		fatal_error("expect_non_negative", "must be non-negative value.");
}

void	expect_color(t_color *c)
{
	if (c->x < 0 || c->x > 255)
		fatal_error("expect_color", "color must be in range [0, 255]");
	if (c->y < 0 || c->y > 255)
		fatal_error("expect_color", "color must be in range [0, 255]");
	if (c->z < 0 || c->z > 255)
		fatal_error("expect_color", "color must be in range [0, 255]");
}

void	expect_normalized(t_vec *v)
{
	t_vec	n;

	if (fabs(vec_length_squared(*v) - 1) > FLT_EPSILON)
	{
		n = vec_unit(*v);
		printf("sqrt : %.20f, epsilon: %.20f\n",
			sqrt(fabs(vec_length_squared(*v) - 1)), FLT_EPSILON);
		printf("normalized [%.10f,%.10f,%.10f]\n", n.x, n.y,
			n.z);
		fatal_error("expect_normalized\n", "vector must be normalized");
	}
	*v = vec_unit(*v);
}
