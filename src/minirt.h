/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:35 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/06 11:55:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define ASPECT_RATIO 1.6
# define WIDTH 512
# define HEIGHT (int)(WIDTH / ASPECT_RATIO)
# define SCREEN_WIDTH 2.0
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "vec.h"

typedef struct s_img			t_img;
typedef struct s_screen			t_screen;
typedef struct s_scene			t_scene;
typedef struct s_camera			t_camera;
typedef struct s_hittable		t_hittable;
typedef struct s_hittable		t_sphere;
typedef struct s_hittable		t_plane;
typedef struct s_hittable		t_cylinder;
typedef struct s_hittable		t_hittable_list;
typedef struct s_light_source	t_light_source;
typedef struct s_lighting		t_lighting;
typedef struct s_ray			t_ray;
typedef struct s_hit_record		t_hit_record;
typedef enum e_element_type		t_element_type;
typedef enum e_hittable_type	t_hittable_type;
typedef struct s_element		t_element;

enum e_element_type {
	E_AMBIENT_LIGHTNING,
	E_CAMERA,
	E_LIGHT,
	E_SPHERE,
	E_PLANE,
	E_CYLINDER,
};

struct s_element {
	t_element_type	element_type;
	// AMBIENT_LIGHTNING
	FLOAT			ambient_lightning_ratio;
	// CAMERA
	t_vec			view_point;
	t_vec			orientation;
	FLOAT			hfov;
	// LIGHT
	t_vec			light_point;
	FLOAT			light_brightness_ratio;
	// SPHERE
	t_vec			sp_center;
	FLOAT			sp_diameter;
	//PLANE
	t_point			pl_point;
	t_vec			pl_normal;
	//CYLINDER
	t_point			cy_center;
	t_vec			cy_orientation;
	FLOAT			cy_diameter;
	FLOAT			cy_height;
	// AMBIENT_LIGHTNING / LIGHT / SPHERE
	t_color			color;
	t_element		*next;
};

struct s_camera {
	t_vec	eye_position; // x,y,z coordinates of the view point
	t_vec	look_at_direction; // 3d normalized orientation vector.
	FLOAT	hfov; // Horizontal field of view in degrees in range [0,180]
};

enum e_hittable_type {
	H_LIST,
	H_SPHERE,
	H_PLANE,
	H_CYLINDER,
};

struct s_hittable {
	// ALL
	t_hittable_type	type;
	t_hittable		*next;
	// H_SPHERE
	t_vec			center;
	FLOAT			radius;
	FLOAT			shineness;
	//H_PLANE
	t_point			position;
	t_vec			normal;
	//CYLINDER
	FLOAT			height;
	t_vec			orientation;
	//COMON
	t_color			ambient_factor;
	t_color			diffuse_factor;
	t_color			specular_factor;
};

struct s_light_source {
	//point light
	t_vec		position; // x,y,z coordinates of the light point
	FLOAT		ratio; // brightness ratio
	t_color		intensity; // (unused in mandatory part)R,G,B colors in range [0-255]
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

// errror.c
void		fatal_error(const char *loc, const char *msg) __attribute__((noreturn));

// parse.c
t_element	*parse(int argc, const char *argv[]);

// translate.c
void		translate(t_scene *scene, t_element *res);

//utils.c
FLOAT		clamp(FLOAT v, FLOAT vmin, FLOAT vmax);
FLOAT		map(FLOAT v, FLOAT vmin, FLOAT vmax, FLOAT tmin, FLOAT tmax);

// ray
t_point		ray_at(const t_ray *r, FLOAT t);

// ray_trace
t_ray		get_ray(t_camera *camera, int x, int y);
t_color		ray_trace(const t_ray *r, t_scene *scene);

// img.c
void		*init_img(void	*mlx_ptr, int width, int height);
void		put_pixel(const t_img *img, int x, int y, int mlx_color);

// hooks.c
void		mlx_keydown_hook(void *win_ptr, int (*handler)(), void *param);
void		mlx_closebutton_hook(void *win_ptr, int (*handler)(), void *param);
int			close_window(t_screen *s);
int			key_handler(int keycode, t_screen *screen);

// hittable.c
bool		hit(const t_hittable *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec);

// hittable_list.c
bool		hittable_list_hit(const t_hittable *head, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec);
void		set_face_normal(t_hit_record *self, const t_ray *r, t_vec outward_normal);

// sphere.c
bool		sphere_hit(const t_sphere *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec);

//plane.c
bool		plane_hit(const t_plane *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec);

// cylinder.c
bool		cylinder_hit(const t_cylinder *self, const t_ray *r, FLOAT t_min, FLOAT t_max, t_hit_record *rec);
#endif
