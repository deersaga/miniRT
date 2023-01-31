/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:37:27 by susami            #+#    #+#             */
/*   Updated: 2023/01/31 14:51:14 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

t_vec	vec_zero(void)
{
	return ((t_vec){.x = 0, .y = 0, .z = 0});
}

t_vec	vec_new(FLOAT x, FLOAT y, FLOAT z)
{
	return ((t_vec){.x = x, .y = y, .z = z});
}

t_point	point_new(FLOAT x, FLOAT y, FLOAT z)
{
	return ((t_point){.x = x, .y = y, .z = z});
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z});
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z});
}

t_vec	vec_mul(t_vec a, t_vec b)
{
	return ((t_vec){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z});
}

t_vec	vec_scalar_mul(FLOAT t, t_vec v)
{
	return ((t_vec){
		.x = v.x * t,
		.y = v.y * t,
		.z = v.z * t});
}

// t must be non-zero value
t_vec	vec_scalar_div(t_vec v, FLOAT t)
{
	return ((t_vec){
		.x = v.x / t,
		.y = v.y / t,
		.z = v.z / t});
}

FLOAT	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x});
}

FLOAT	vec_length_squvred(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

FLOAT	vec_length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec	vec_unit(t_vec v)
{
	FLOAT	len;

	len = vec_length(v);
	if (len == 0)
		return (v);
	return ((t_vec){
		.x = v.x / len,
		.y = v.y / len,
		.z = v.z / len});
}
