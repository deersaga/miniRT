/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:59:15 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 14:59:46 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

FLOAT clamp(FLOAT v, FLOAT vmin, FLOAT vmax)
{
	if (v > vmax)
		return (vmax);
	else if (v < vmin)
		return (vmin);
	else
		return (v);
}

// map(𝑣,𝑣𝑚𝑖𝑛,𝑣𝑚𝑎𝑥,𝑡𝑚𝑖𝑛,𝑡𝑚𝑎𝑥) = 𝑡𝑚𝑖𝑛 + (𝑡𝑚𝑎𝑥–𝑡𝑚𝑖𝑛) × constrain(𝑣,𝑣𝑚𝑖𝑛,𝑣𝑚𝑎𝑥) / 𝑣𝑚𝑎𝑥−𝑣𝑚𝑖𝑛
FLOAT map(FLOAT v, FLOAT vmin, FLOAT vmax, FLOAT tmin, FLOAT tmax)
{
	return (tmin + (tmax - tmin) * clamp(v, vmin, vmax) / (vmax - vmin));
}