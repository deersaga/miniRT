/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:15:34 by susami            #+#    #+#             */
/*   Updated: 2023/01/31 15:13:29 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "minirt.h"

typedef struct s_vec	t_vec;
typedef struct s_vec	t_point;
typedef struct s_vec	t_color;


t_vec	vec_mul(t_vec a, t_vec b);
t_vec	vec_scalar_mul(FLOAT t, t_vec v);
t_vec	vec_scalar_div(t_vec v, FLOAT t);


struct s_vec {
	FLOAT	x;
	FLOAT	y;
	FLOAT	z;
};

t_vec	vec_zero(void);
t_vec	vec_new(FLOAT x, FLOAT y, FLOAT z);
t_point	point_new(FLOAT x, FLOAT y, FLOAT z);
t_color	color_new(FLOAT x, FLOAT y, FLOAT z);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, t_vec b);
t_vec	vec_scalar_mul(FLOAT t, t_vec v);
t_vec	vec_scalar_div(t_vec v, FLOAT t);
FLOAT	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
FLOAT	vec_length_squared(t_vec a);
FLOAT	vec_length(t_vec a);
t_vec	vec_unit(t_vec a);

t_color	color_black(void);
t_color	color_white(void);
int		get_mlx_color(t_color c);

FLOAT	clamp(FLOAT v, FLOAT vmin, FLOAT vmax);
FLOAT	map(FLOAT v, FLOAT vmin, FLOAT vmax, FLOAT tmin, FLOAT tmax);

#endif
