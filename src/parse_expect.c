/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expect2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:15:03 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 00:15:04 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"
#include "tokenize.h"

void	expect_id_tok(const t_token **rest, const t_token *tok,
		t_element_type id)
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
