/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:30 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/08 20:57:41 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOR_NORM_H
# define FOR_NORM_H

# include "vec.h"

typedef struct s_range		t_range;
typedef struct s_quad_eq	t_quad_eq;

struct s_range {
	FLOAT	min;
	FLOAT	max;
};

struct s_quad_eq {
	FLOAT	a;
	FLOAT	b;
	FLOAT	hb;
	FLOAT	c;
	FLOAT	discriminant;
	FLOAT	t;
	FLOAT	root;
};

#endif