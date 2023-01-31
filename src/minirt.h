/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:35 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 16:42:04 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 800
# define HEIGHT 512
# define FLOAT float

#include <stdio.h>
#include "vec.h"

typedef struct s_img	t_img;
typedef struct s_screen	t_screen;
typedef struct s_scene	t_scene;

struct s_scene {};

struct s_img {
	void	*mlx_ptr;
	void	*ptr;
	char	*data;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		bytes_per_line;
	int		endian;
};

struct s_screen {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
};

// errror.c
void	fatal_error(const char *loc, const char *msg);

// parse.c
t_scene	parse(int argc, const char *argv[]);

//utils.c
FLOAT	clamp(FLOAT v, FLOAT vmin, FLOAT vmax);
FLOAT	map(FLOAT v, FLOAT vmin, FLOAT vmax, FLOAT tmin, FLOAT tmax);

#endif
