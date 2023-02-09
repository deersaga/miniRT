/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:57:58 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 02:50:41 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"

void	element_add(t_element *head, t_element *elem)
{
	while (head->next)
	{
		head = head->next;
	}
	head->next = elem;
}

void	print_element(t_element *head)
{
	while (head)
	{
		printf("type %d color [%f %f %f]\n", head->element_type,
			head->color.x, head->color.y, head->color.z);
		head = head->next;
	}
}

bool	is_acl(const t_token *tok)
{
	t_element_type	id;

	id = tok->id;
	if (tok->type != TK_ID)
		return (false);
	if (id == E_AMBIENT_LIGHTNING || id == E_CAMERA || id == E_LIGHT)
		return (true);
	return (false);
}

// // Validate orientation vector: must be normalized
// // Validate FOV: must be in range [0, 180]
// // Validate color: must be in range [0, 255]
// // Validate light ratio: must be in range [0, 255]
// void	validate_element(t_element *elem)
// {
// 	const t_element_type	type = elem->element_type;

// 	if (E_AMBIENT_LIGHTNING <= type && type <= E_CYLINDER && type != E_CAMERA)
// 		expect_color(&elem->color);
// 	if (type == E_AMBIENT_LIGHTNING || type == E_LIGHT || type == E_CAMERA)
// 		expect_once(elem->element_type);
// 	if (elem->element_type == E_AMBIENT_LIGHTNING)
// 		expect_ratio(elem->ambient_lightning_ratio);
// 	if (elem->element_type == E_CAMERA)
// 	{
// 		expect_normalized(&elem->orientation);
// 		expect_fov(elem->hfov);
// 	}
// 	if (elem->element_type == E_LIGHT)
// 		expect_ratio(elem->light_brightness_ratio);
// 	if (elem->element_type == E_SPHERE)
// 		expect_non_negative(elem->sp_diameter);
// 	if (elem->element_type == E_PLANE)
// 		expect_normalized(&elem->pl_normal);
// 	if (elem->element_type == E_CYLINDER)
// 	{
// 		expect_normalized(&elem->cy_orientation);
// 		expect_non_negative(elem->cy_diameter);
// 		expect_non_negative(elem->cy_height);
// 	}
// }

t_element	*elementize(const t_token *tok)
{
	t_element		head;
	t_element		*cur;

	head.next = NULL;
	cur = &head;
	while (tok && tok->type != TK_EOF)
	{
		if (consume_newline_token(&tok, tok))
			continue ;
		else if (is_acl(tok))
			cur->next = parse_acl((const t_token **)&tok, tok);
		else if (tok->type == TK_ID && tok->id == E_SPHERE)
			cur->next = parse_sphere((const t_token **)&tok, tok);
		else if (tok->type == TK_ID && tok->id == E_PLANE)
			cur->next = parse_plane((const t_token **)&tok, tok);
		else if (tok->type == TK_ID && tok->id == E_CYLINDER)
			cur->next = parse_cylinder((const t_token **)&tok, tok);
		else
			fatal_error("elementize", "Unexpected token");
		validate_element(cur->next);
		cur = cur->next;
	}
	return (head.next);
}
