/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degrees_to_radians.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:40:50 by susami            #+#    #+#             */
/*   Updated: 2023/02/13 13:41:11 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

FLOAT	degrees_to_radians(FLOAT degrees)
{
	return (degrees * M_PI / 180);
}
