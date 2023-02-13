/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:15:34 by susami            #+#    #+#             */
/*   Updated: 2023/02/13 13:38:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# define FLOAT double

typedef struct s_vec	t_vec;
typedef struct s_vec	t_point;
typedef struct s_vec	t_color;
typedef struct s_range	t_range;

t_vec	vec_mul(t_vec a, t_vec b);
t_vec	vec_scalar_mul(FLOAT t, t_vec v);
t_vec	vec_scalar_div(t_vec v, FLOAT t);

struct s_vec {
	FLOAT	x;
	FLOAT	y;
	FLOAT	z;
};

t_vec	vec_new(FLOAT x, FLOAT y, FLOAT z);
t_point	point_new(FLOAT x, FLOAT y, FLOAT z);
t_color	color_new(FLOAT x, FLOAT y, FLOAT z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, t_vec b);
t_vec	vec_scalar_mul(FLOAT t, t_vec v);
t_vec	vec_scalar_div(t_vec v, FLOAT t);
FLOAT	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
FLOAT	vec_length_squared(t_vec v);
FLOAT	vec_length(t_vec v);
t_vec	vec_unit(t_vec v);

#endif
