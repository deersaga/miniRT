/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:37:27 by susami            #+#    #+#             */
/*   Updated: 2023/02/08 19:10:28 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

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

FLOAT	vec_length_squared(t_vec v)
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
