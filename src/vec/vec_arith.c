/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_arith.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:37:27 by susami            #+#    #+#             */
/*   Updated: 2023/02/09 21:33:27 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

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
