/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/06 11:38:21 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <float.h> // FLT_EPSILON
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

void	expect_normalized(t_vec *v)
{
	if (fabs(vec_length_squared(*v) - 1) > FLT_EPSILON)
	{
		t_vec	n = vec_unit(*v);
		dprintf(STDERR_FILENO, "sqrt : %.20f, epsilon: %.20f\n", sqrt(fabs(vec_length_squared(*v) - 1)), FLT_EPSILON)
;
		dprintf(STDERR_FILENO, "normalized [%.10f,%.10f,%.10f]\n", n.x, n.y, n.z);
		//fatal_error("expect_normalized", "Vector must be normalized.");
		dprintf(STDERR_FILENO, "expect_normalized\n");
	}
	*v = vec_unit(*v);
}

void	expect_ratio(FLOAT val)
{
	if (val < 0 || val > 1.0)
		fatal_error("expect_ratio", "ratio must be in range [0.0, 1.0]");
}

void	expect_fov(FLOAT val)
{
	if (val < 0 || val > 180.0)
		fatal_error("expect_fov", "FOV must be in range [0.0, 180.0]");
}

void	expect_color(t_color *c)
{
	if (c->x < 0 || c->x > 255)
		fatal_error("expect_color", "color must be in range [0, 255]");
	if (c->y < 0 || c->y > 255)
		fatal_error("expect_color", "color must be in range [0, 255]");
	if (c->z < 0 || c->z > 255)
		fatal_error("expect_color", "color must be in range [0, 255]");
}

// Validate orientation vector: must be normalized
// Validate FOV: must be in range [0, 180]
// Validate color: must be in range [0, 255]
// Validate light ratio: must be in range [0, 255]
void	validate_element(t_element *elem)
{
	static bool	exist_A;
	static bool	exist_L;
	static bool	exist_C;

	if (elem->element_type == E_AMBIENT_LIGHTNING
		|| elem->element_type == E_LIGHT
		|| elem->element_type == E_SPHERE
		|| elem->element_type == E_PLANE
		|| elem->element_type == E_CYLINDER)
		expect_color(&elem->color);
	if (elem->element_type == E_AMBIENT_LIGHTNING)
	{
		if (exist_A == true)
			fatal_error("validation", "multiple Ambient light is forbidden!");
		exist_A = true;
		expect_ratio(elem->ambient_lightning_ratio);
	}
	if (elem->element_type == E_CAMERA)
	{
		if (exist_C == true)
			fatal_error("validation", "multiple Ambient light is forbidden!");
		exist_C = true;
		expect_normalized(&elem->orientation);
		expect_fov(elem->hfov);
	}
	if (elem->element_type == E_LIGHT)
	{
		if (exist_L == true)
			fatal_error("validation", "multiple Ambient light is forbidden!");
		exist_L = true;
		expect_ratio(elem->light_brightness_ratio);
	}
	if (elem->element_type == E_PLANE)
		expect_normalized(&elem->pl_normal);
	if (elem->element_type == E_CYLINDER)
		expect_normalized(&elem->cy_orientation);
}

bool	consume_newline_token(const t_token **rest, const t_token *tok)
{
	bool	consumed;

	consumed = false;
	while (tok->type == TK_NL)
	{
		tok = tok->next;
		consumed = true;
	}
	*rest = tok;
	return (consumed);
}


t_element	*internal_parse(const t_token *tok)
{
	t_element		head;
	t_element		*cur;

	head.next = NULL;
	cur = &head;
	while (tok && tok->type != TK_EOF)
	{
		if (consume_newline_token(&tok, tok))
			continue ;
		else if (is_element(tok, E_AMBIENT_LIGHTNING))
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
		validate_element(cur->next);
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
