/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:49:19 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 03:08:11 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "tokenize.h"
# include "element.h"
# include <float.h>
# include <math.h>
# include <stdbool.h>

void		expect_id_tok(const t_token **rest, const t_token *tok,
				t_element_type id);
FLOAT		expect_num_tok(const t_token **rest, const t_token *tok);
t_vec		expect_vec_tok(const t_token **rest, const t_token *tok);
void		expect_newline_or_eof(const t_token **rest, const t_token *tok);
bool		consume_newline_token(const t_token **rest, const t_token *tok);

t_element	*parse_acl(const t_token **rest, const t_token *tok);
t_element	*parse_ambient_light(const t_token **rest, const t_token *tok);
t_element	*parse_camera(const t_token **rest, const t_token *tok);
t_element	*parse_light(const t_token **rest, const t_token *tok);
t_element	*parse_sphere(const t_token **rest, const t_token *tok);
t_element	*parse_plane(const t_token **rest, const t_token *tok);
t_element	*parse_cylinder(const t_token **rest, const t_token *tok);

#endif