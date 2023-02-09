/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:49:19 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 20:20:09 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "tokenize.h"
# include <float.h>
# include <math.h>

void		expect_id_tok(const t_token **rest, const t_token *tok,
				t_element_type id);
FLOAT		expect_num_tok(const t_token **rest, const t_token *tok);
t_vec		expect_vec_tok(const t_token **rest, const t_token *tok);
void		expect_newline_or_eof(const t_token **rest, const t_token *tok);
bool		consume_newline_token(const t_token **rest, const t_token *tok);

void		expect_ratio(FLOAT val);
void		expect_fov(FLOAT val);
void		expect_non_negative(FLOAT val);
void		expect_color(t_color *c);
void		expect_normalized(t_vec *v);
void		expect_once(t_element_type type);

t_element	*cylinder_element_alloc(t_point center, t_vec orientation,
				t_range r_and_h, t_color color);
t_element	*plane_element_alloc(t_point point, t_vec normal, t_color color);
t_element	*sphere_element_alloc(t_vec center, FLOAT diameter, t_color color);
t_element	*light_element_alloc(t_vec p, FLOAT ratio, t_color color);
t_element	*camera_element_alloc(t_vec p, t_vec dir, FLOAT hfov);
t_element	*ambient_element_alloc(FLOAT ratio, t_color color);

t_element	*acl_elem_new(const t_token **rest, const t_token *tok);
t_element	*parse_ambient_light(const t_token **rest, const t_token *tok);
t_element	*parse_camera(const t_token **rest, const t_token *tok);
t_element	*parse_light(const t_token **rest, const t_token *tok);
t_element	*parse_sphere(const t_token **rest, const t_token *tok);
t_element	*parse_plane(const t_token **rest, const t_token *tok);
t_element	*parse_cylinder(const t_token **rest, const t_token *tok);

void		validate_element(t_element *elem);
void		element_add(t_element *head, t_element *elem);
t_element	*elementize(const t_token *tok);
void		validate_element(t_element *elem);

#endif