/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:43:37 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 01:47:42 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H
# include "minirt.h"

typedef struct s_token		t_token;

enum e_token_type {
	TK_NUM,
	TK_ID,
	TK_VEC,
	TK_NL,
	TK_EOF,
};
typedef enum e_token_type	t_token_type;

struct s_token {
	t_token_type	type;
	t_element_type	id;
	FLOAT			num1;
	FLOAT			num2;
	FLOAT			num3;
	t_token			*next;
};

void	free_tok(t_token *tok);
t_token	*tokenize(const char *buf);
t_token	*token_alloc(t_token_type type);
bool	is_identifier(const char *s);
bool	is_number(const char *s);
bool	is_vector(const char *s);
bool	consume_blank(const char **rest, const char *buff);
bool	consume_number(const char **rest, const char *s);
bool	consume_comma(const char **rest, const char *s);
bool	consume_newline(const char **rest, const char *buf);
#endif
