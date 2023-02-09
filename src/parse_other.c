/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_new_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:35:29 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 20:20:03 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

t_element	*parse_sphere(const t_token **rest, const t_token *tok)
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

t_element	*parse_plane(const t_token **rest, const t_token *tok)
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

t_element	*parse_cylinder(const t_token **rest, const t_token *tok)
{
	t_element	*elem;

	expect_id_tok(&tok, tok, E_CYLINDER);
	elem = cylinder_element_alloc(
			expect_vec_tok(&tok, tok),
			expect_vec_tok(&tok, tok),
			range_new(expect_num_tok(&tok, tok), expect_num_tok(&tok, tok)),
			expect_vec_tok(&tok, tok)
			);
	expect_newline_or_eof(&tok, tok);
	*rest = tok;
	return (elem);
}
