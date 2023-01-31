/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:35 by katakagi          #+#    #+#             */
/*   Updated: 2023/01/31 17:43:25 by katakagi         ###   ########.fr       */
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
typedef struct s_material	t_material;
typedef struct s_scene	t_scene;
typedef struct s_shape	t_shape;
typedef struct s_light_source	t_light_source;
typedef enum e_shape_kind t_shape_kind;
typedef enum e_light_kind t_light_kind;

typedef struct s_proto	t_prot;

struct s_material {};

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

struct s_scene {
	t_shape			shapes;
	t_light_source	light_sources;
	t_color			ambient_intesity;
	FLOAT			air_refraction;
	t_vec			eye_position;
	t_vec			look_at;
	FLOAT			screen_distance;
	FLOAT			HFOV;
};

enum e_shape_kind {
	SPHERE,
	PLANE,
	CYLINDER,
};

struct s_shape {
	t_shape_kind	kind;
	t_material		*material;
	t_shape			*next;

	//sphere, cylinder
	t_vec			center;
	FLOAT			radius;
	// //cylinder
	// FLOAT			height;
	// t_vec			orientation; // (0, 1, 0)
	// //plane
	// t_vec			normal;
	// t_vec			position;
};

enum e_light_kind {
	POINT,
	DIRECTIONAL,
};

struct s_light_source {
	t_light_kind	kind;
	t_fcolor		intencity;
	t_light_source	*next;

	//point light
	t_vec			position;
	//directional light
	t_vec			direction;
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
