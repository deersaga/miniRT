/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:29:30 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/08 19:30:32 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOR_NORM_H
# define FOR_NORM_H

# include "vec.h"

typedef struct s_range	t_range;

struct s_range {
	FLOAT	min;
	FLOAT	max;
};

#endif