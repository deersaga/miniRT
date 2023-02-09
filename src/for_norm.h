/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:30 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 20:08:18 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOR_NORM_H
# define FOR_NORM_H

# include "vec.h"

typedef struct s_range				t_range;
typedef struct s_quad_eq			t_quad_eq;
typedef struct s_dot				t_dot;
typedef struct s_display_coordinate	t_display_coordinate;

struct s_quad_eq {
	FLOAT	a;
	FLOAT	b;
	FLOAT	half_b;
	FLOAT	c;
	FLOAT	discriminant;
	FLOAT	t;
	FLOAT	root;
};

struct s_dot {
	FLOAT	nl;
	FLOAT	vr;
	FLOAT	vr_pow_alpha;
};

struct s_display_coordinate {
	t_vec	ey;
	t_vec	dx;
	t_vec	dy;
	FLOAT	u;
	FLOAT	v;
};

// FLOAT	clamp(FLOAT v, t_range vr);
// FLOAT	map(FLOAT v, t_range vr, t_range tr);
// t_range	range_new(FLOAT min, FLOAT max);

#endif