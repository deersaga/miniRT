/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:35 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/01 10:29:02 by susami           ###   ########.fr       */
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
typedef struct s_camera	t_camera;
typedef struct s_sphere	t_sphere;
typedef struct s_light_source	t_light_source;

typedef struct s_proto	t_prot;

// struct s_proto {
// 	char			*idetifier;
// 	FLOAT			ambient_ratio;
// 	t_vec			eye_position;
// 	t_vec			look_at;
// 	FLOAT			HFOV;
// 	t_vec			light_pos;
// 	FLOAT			light_intencity_ratio;
// 	t_vec			center;
// 	FLOAT			radius;
// 	t_color			color;
// };

struct s_camera {
 	t_vec			eye_position; // x,y,z coordinates of the view point
 	t_vec			look_at_direction; // 3d normalized orientation vector.
 	FLOAT			hfov; // Horizontal field of view in degrees in range [0,180]
};

struct s_sphere {
	//sphere
	t_vec			center;
	FLOAT			radius;
	t_color			color;
};

struct s_light_source {
	//point light
	t_vec		position; // x,y,z coordinates of the light point
	FLOAT		ratio; // brightness ratio
	t_color		color; // (unused in mandatory part)R,G,B colors in range [0-255]
};

struct s_scene {
	t_sphere		sphere;
	t_light_source	light_source;
	t_camera		camera;
};

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
