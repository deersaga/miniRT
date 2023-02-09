/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:04 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 21:32:11 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tokenize.h"

void	free_tok(t_token *tok)
{
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		free(tok);
		tok = next;
	}
}

t_token	*token_alloc(t_token_type type)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
	tok->type = type;
	return (tok);
}

// Identifier
bool	is_identifier(const char *s)
{
	static const char	*identifiers[] = {"A", "C", "L", "sp", "pl", "cy"};
	size_t				i;

	i = 0;
	while (i < E_END)
	{
		if (!ft_memcmp(s, identifiers[i], ft_strlen(identifiers[i])))
			return (true);
		i++;
	}
	return (false);
}

// Number
// 1xxx
// .1xxx

bool	is_number(const char *s)
{
	if (!consume_number(&s, s))
		return (false);
	if (*s == ' ' || *s == '\0' || *s == '\n')
		return (true);
	return (false);
}

// Vector

// A 0.2 255,255,255
// ^ ^   ^  ^^  ^^
bool	is_vector(const char *s)
{
	if (!consume_number(&s, s))
		return (false);
	if (!consume_comma(&s, s))
		return (false);
	if (!consume_number(&s, s))
		return (false);
	if (!consume_comma(&s, s))
		return (false);
	if (!consume_number(&s, s))
		return (false);
	if (*s != ' ' && *s != '\0' && *s != '\n')
		return (false);
	return (true);
}
