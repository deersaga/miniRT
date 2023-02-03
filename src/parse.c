/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/03 11:50:36 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "minirt.h"
#include "tokenize.h"

t_element	*cylinder_element_alloc(t_point center, t_vec orientation, FLOAT diameter, FLOAT height, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_CYLINDER;
	self->cy_center = center;
	self->cy_orientation = orientation;
	self->cy_diameter = diameter;
	self->cy_height = height;
	self->color = color;
	return (self);
}

t_element	*plane_element_alloc(t_point point, t_vec normal, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_PLANE;
	self->pl_point = point;
	self->pl_normal = normal;
	self->color = color;
	return (self);
}

t_element	*sphere_element_alloc(t_vec center, FLOAT diameter, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_SPHERE;
	self->sp_center = center;
	self->sp_diameter = diameter;
	self->color = color;
	return (self);
}

t_element	*light_element_alloc(t_vec p, FLOAT ratio, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_LIGHT;
	self->light_point = p;
	self->light_brightness_ratio = ratio;
	self->color = color;
	return (self);
}

t_element	*camera_element_alloc(t_vec p, t_vec dir, FLOAT hfov)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_CAMERA;
	self->view_point = p;
	self->orientation = dir;
	self->hfov = hfov;
	return (self);
}

t_element	*ambient_element_alloc(FLOAT ratio, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_AMBIENT_LIGHTNING;
	self->ambient_lightning_ratio = ratio;
	self->color = color;
	return (self);
}

void	element_add(t_element *head, t_element *elem)
{
	while (head->next)
	{
		head = head->next;
	}
	head->next = elem;
}

bool	is_element(const t_token *tok, t_element_type id)
{
	if (tok->type == TK_ID && tok->id == id)
		return (true);
	return (false);
}

void	expect_id_tok(const t_token **rest, const t_token *tok, t_element_type id)
{
	if (tok->type != TK_ID || tok->id != id)
		fatal_error("expect_id_tok", "Unexpected token");
	*rest = tok->next;
}

FLOAT	expect_num_tok(const t_token **rest, const t_token *tok)
{
	if (tok->type != TK_NUM)
		fatal_error("expect_num_tok", "Unexpected token");
	*rest = tok->next;
	return (tok->num1);
}

t_vec	expect_vec_tok(const t_token **rest, const t_token *tok)
{
	if (tok->type != TK_VEC)
		fatal_error("expect_vec_tok", "Unexpected token");
	*rest = tok->next;
	return (vec_new(tok->num1, tok->num2, tok->num3));
}

void	expect_newline_or_eof(const t_token **rest, const t_token *tok)
{
	if (tok->type != TK_NL && tok->type != TK_EOF)
		fatal_error("expect_newline_or_eof", "Unexpected token");
	*rest = tok->next;
}

t_element	*ambient_light(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_AMBIENT_LIGHTNING);
	elem = ambient_element_alloc(
			expect_num_tok(&tok, tok),
			expect_vec_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}

t_element	*camera(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_CAMERA);
	elem = camera_element_alloc(
			expect_vec_tok(&tok, tok),
			expect_vec_tok(&tok, tok),
			expect_num_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}

t_element	*light(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_LIGHT);
	elem = light_element_alloc(
			expect_vec_tok(&tok, tok),
			expect_num_tok(&tok, tok),
			expect_vec_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}

t_element	*sphere(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_SPHERE);
	elem = sphere_element_alloc(
			expect_vec_tok(&tok, tok),
			expect_num_tok(&tok, tok),
			expect_vec_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}

t_element	*plane(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_PLANE);
	elem = plane_element_alloc(
			expect_vec_tok(&tok, tok),
			expect_vec_tok(&tok, tok),
			expect_vec_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}

t_element	*cylinder(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_CYLINDER);
	elem = cylinder_element_alloc(
			expect_vec_tok(&tok, tok),
			expect_vec_tok(&tok, tok),
			expect_num_tok(&tok, tok),
			expect_num_tok(&tok, tok),
			expect_vec_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}

t_element	*internal_parse(t_token *tok)
{
	t_element		head;
	t_element		*cur;

	head.next = NULL;
	cur = &head;
	while (tok && tok->type != TK_EOF)
	{
		if (is_element(tok, E_AMBIENT_LIGHTNING))
			cur->next = ambient_light((const t_token **)&tok, tok);
		else if (is_element(tok, E_CAMERA))
			cur->next = camera((const t_token **)&tok, tok);
		else if (is_element(tok, E_LIGHT))
			cur->next = light((const t_token **)&tok, tok);
		else if (is_element(tok, E_SPHERE))
			cur->next = sphere((const t_token **)&tok, tok);
		else if (is_element(tok, E_PLANE))
			cur->next = plane((const t_token **)&tok, tok);
		else if (is_element(tok, E_CYLINDER))
			cur->next = cylinder((const t_token **)&tok, tok);
		else
			fatal_error("parse", "Unexpected token");
		cur = cur->next;
	}
	return (head.next);
}

t_element	*parse(int argc, const char *argv[])
{
	int				fd;
	char			*tail;
	char			buf[1000];
	int				rc;
	t_token			*tok;
	t_element		*elements;

	{
		errno = 0;
		if (argc != 2)
			fatal_error("parse", "[Usage]: ./miniRT config_file");
		tail = strrchr(argv[1], '.');
		if (tail == NULL || strcmp(tail, ".rt"))
			fatal_error("parse", "extension must be .rt");
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			fatal_error("parse", NULL);
		rc = read(fd, buf, 999);
		buf[rc] = '\0';
		close(fd);
	}
	tok = tokenize(buf);
	elements = internal_parse(tok);
	free_tok(tok);
	return (elements);
}
