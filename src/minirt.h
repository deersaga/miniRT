/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:35 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/01 12:07:24 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define ASPECT_RATIO 1.6
# define WIDTH 512
# define HEIGHT (int)(WIDTH / ASPECT_RATIO)
# define SCREEN_WIDTH 2.0
#include <stdio.h>
#include "vec.h"

typedef struct s_img	t_img;
typedef struct s_screen	t_screen;
typedef struct s_scene	t_scene;
typedef struct s_camera	t_camera;
typedef struct s_sphere	t_sphere;
typedef struct s_light_source	t_light_source;
typedef struct s_ray	t_ray;
typedef struct s_hit_record	t_hit_record;

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

struct s_hit_record {
	t_point		p;
	t_vec		normal;
	t_sphere	*sphere_ptr;
};

struct s_ray {
	t_point	origin;
	t_vec	direction;
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

//ray
t_ray	get_ray(t_camera *camera, int x, int y);
t_color	ray_trace(const t_ray *r, t_scene *scene);

// img.c
void	*init_img(void	*mlx_ptr, int width, int height);
void	put_pixel(const t_img *img, int x, int y, int mlx_color);

// hooks.c
void	mlx_closebutton_hook(void *win_ptr, int (*handler)(), void *param);
int		close_window(t_screen *s);

#endif
