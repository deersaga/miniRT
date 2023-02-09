/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 03:07:51 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 03:10:01 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H
# define BORDER 1000000000
# include "vec.h"

typedef enum e_element_type	t_element_type;
typedef struct s_element	t_element;
typedef struct s_token		t_token;

enum e_element_type {
	E_AMBIENT_LIGHTNING,
	E_CAMERA,
	E_LIGHT,
	E_SPHERE,
	E_PLANE,
	E_CYLINDER,
	E_END,
};

struct s_element {
	t_element_type	element_type;

	FLOAT			ambient_lightning_ratio;

	t_vec			view_point;
	t_vec			orientation;
	FLOAT			hfov;

	t_vec			light_point;
	FLOAT			light_brightness_ratio;

	t_vec			sp_center;
	FLOAT			sp_diameter;

	t_point			pl_point;
	t_vec			pl_normal;

	t_point			cy_center;
	t_vec			cy_orientation;
	FLOAT			cy_diameter;
	FLOAT			cy_height;

	t_color			color;
	t_element		*next;
};

t_element	*cylinder_element_alloc(t_point center, t_vec orientation,
				t_range r_and_h, t_color color);
t_element	*plane_element_alloc(t_point point, t_vec normal, t_color color);
t_element	*sphere_element_alloc(t_vec center, FLOAT diameter, t_color color);
t_element	*light_element_alloc(t_vec p, FLOAT ratio, t_color color);
t_element	*camera_element_alloc(t_vec p, t_vec dir, FLOAT hfov);
t_element	*ambient_element_alloc(FLOAT ratio, t_color color);

void		expect_ratio(FLOAT val);
void		expect_fov(FLOAT val);
void		expect_non_negative(FLOAT val);
void		expect_color(t_color *c);
void		expect_normalized(t_vec *v);
void		expect_not_too_big(FLOAT val);
void		expect_not_too_big_or_small_vec(t_vec *v);
void		expect_once(t_element_type type);

t_element	*elementize(const t_token *tok);
void		validate_element(t_element *elem);
void		validate_acl(t_element *elem);
void		validate_sphere(t_element *elem);
void		validate_plane(t_element *elem);
void		validate_cylinder(t_element *elem);
void		element_add(t_element *head, t_element *elem);

#endif
