/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:35 by katakagi          #+#    #+#             */
/*   Updated: 2023/03/22 16:51:26 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGHT 320
# define WIDTH 512
# define SCREEN_WIDTH 2.0
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include "vec.h"
# include "libft.h"
# include "element.h"

typedef struct s_img				t_img;
typedef struct s_screen				t_screen;
typedef struct s_scene				t_scene;
typedef struct s_camera				t_camera;
typedef struct s_hittable			t_hittable;
typedef struct s_hittable			t_sphere;
typedef struct s_hittable			t_plane;
typedef struct s_hittable			t_cylinder;
typedef struct s_hittable			t_hittable_list;
typedef struct s_light_source		t_light_source;
typedef struct s_lighting			t_lighting;
typedef struct s_ray				t_ray;
typedef struct s_hit_record			t_hit_record;
typedef enum e_hittable_type		t_hittable_type;
typedef struct s_range				t_range;
typedef struct s_quad_eq			t_quad_eq;
typedef struct s_dot				t_dot;
typedef struct s_display_coordinate	t_display_coordinate;

struct s_quad_eq {
	FLOAT	a;
	FLOAT	b;
	FLOAT	half_b;
	FLOAT	c;
	FLOAT	discriminant;
	FLOAT	t;
	FLOAT	root;
};

struct s_dot {
	FLOAT	nl;
	FLOAT	vr;
	FLOAT	vr_pow_alpha;
};

struct s_display_coordinate {
	t_vec	dx;
	t_vec	dy;
	FLOAT	u;
	FLOAT	v;
};

struct s_camera {
	t_vec	eye_position;
	t_vec	look_at_direction;
	t_vec	screen_center;
	FLOAT	hfov;
	FLOAT	aspect_ratio;
};

enum e_hittable_type {
	H_LIST,
	H_SPHERE,
	H_PLANE,
	H_CYLINDER,
};

struct s_hittable {
	t_hittable_type	type;
	t_hittable		*next;

	t_vec			center;
	FLOAT			radius;
	FLOAT			shineness;

	t_point			position;
	t_vec			normal;

	FLOAT			height;
	t_vec			orientation;

	t_color			ambient_factor;
	t_color			diffuse_factor;
	t_color			specular_factor;
};

struct s_light_source {
	t_vec		position;
	t_color		intensity;
};

struct s_lighting {
	t_vec	direction;
	t_color	intensity;
	FLOAT	distance;
};

struct s_scene {
	t_hittable		list;
	t_light_source	light_source;
	t_camera		camera;
	t_color			ambient_intensity;
};

struct s_hit_record {
	FLOAT				t;
	t_point				p;
	t_vec				normal;
	const t_hittable	*hittable_ptr;
	bool				front_face;
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

struct s_range {
	FLOAT	min;
	FLOAT	max;
};

// error.c
void		fatal_error(const char *loc, const char *msg)
			__attribute__((noreturn));

// parse.c
t_element	*parse(int argc, const char *argv[]);

// translate.c
void		translate(t_scene *scene, t_element *res);

// ft_strtod.c
double		ft_strtod(const char *str, char **rest);

// degrees_to_radians.c
FLOAT		degrees_to_radians(FLOAT degrees);

// range.c
t_range		range_new(FLOAT min, FLOAT max);
FLOAT		clamp(FLOAT v, t_range vr);
FLOAT		map(FLOAT v, t_range vr, t_range tr);

// ray
t_point		ray_at(const t_ray *r, FLOAT t);

// ray_trace
t_ray		get_ray(t_camera *camera, int x, int y);
t_color		ray_trace(const t_ray *r, t_scene *scene);

// img.c
void		*init_img(void	*mlx_ptr, int width, int height);
void		put_pixel(const t_img *img, int x, int y, int mlx_color);

// color.c
int			get_mlx_color(t_color c);

// hooks.c
void		mlx_keydown_hook(void *win_ptr, int (*handler)(), void *param);
void		mlx_closebutton_hook(void *win_ptr, int (*handler)(), void *param);
int			close_window(t_screen *s);
int			key_handler(int keycode, t_screen *screen);
int			expose_handler(t_screen *screen);

// hittable.c
bool		hit(const t_hittable *self,
				const t_ray *r, t_range tr, t_hit_record *rec);

// hittable_list.c
bool		hittable_list_hit(const t_hittable *head, const t_ray *r,
				t_range tr, t_hit_record *rec);
void		set_face_normal(t_hit_record *self, const t_ray *r,
				t_vec outward_normal);

// sphere.c
bool		sphere_hit(const t_sphere *self,
				const t_ray *r, t_range tr, t_hit_record *rec);

//plane.c
bool		plane_hit(const t_plane *self,
				const t_ray *r, t_range tr, t_hit_record *rec);

// cylinder.c
bool		cylinder_hit(const t_cylinder *self,
				const t_ray *r, t_range tr, t_hit_record *rec);

//testcode.c
void		farland_test(t_scene *scene, t_screen *screen);
void		draw_image(t_screen *screen, t_scene *scene);

#endif
