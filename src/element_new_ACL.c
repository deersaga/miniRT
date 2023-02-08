/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_new_ACL.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:35:29 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 01:45:22 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

t_element	*ambient_light_elem_new(const t_token **rest, const t_token *tok)
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

t_element	*camera_elem_new(const t_token **rest, const t_token *tok)
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

t_element	*light_elem_new(const t_token **rest, const t_token *tok)
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

t_element	*acl_elem_new(const t_token **rest, const t_token *tok)
{
	t_element_type	id;

	id = tok->id;
	if (id == E_AMBIENT_LIGHTNING)
		return (ambient_light_elem_new(rest, tok));
	else if (id == E_CAMERA)
		return (camera_elem_new(rest, tok));
	else if (id == E_LIGHT)
		return (light_elem_new(rest, tok));
	return (NULL);
}
