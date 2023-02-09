/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:04 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/09 23:03:43 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tokenize.h"
#include <string.h> //ft_memcmp

void	print_tokens(t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		printf("token type: %d, id: %d, [%f %f %f]\n", cur->type, cur->id,
			cur->num1, cur->num2, cur->num3);
		cur = cur->next;
	}
}

// Identifier

t_token	*identifier(const char **rest, const char *buf)
{
	t_token				*tok;
	t_element_type		e_type;
	static const char	*identifiers[] = {"A", "C", "L", "sp", "pl", "cy"};

	tok = token_alloc(TK_ID);
	e_type = E_AMBIENT_LIGHTNING;
	while (e_type < E_END)
	{
		if (!ft_memcmp(buf, identifiers[e_type],
				ft_strlen(identifiers[e_type])))
		{
			tok->id = e_type;
			buf += ft_strlen(identifiers[e_type]);
			break ;
		}
		e_type++;
	}
	*rest = buf;
	return (tok);
}

// Number

t_token	*number(const char **rest, const char *s)
{
	t_token	*tok;

	tok = token_alloc(TK_NUM);
	tok->num1 = ft_strtod(s, (char **)rest);
	return (tok);
}

// Vector

t_token	*vector(const char **rest, const char *buf)
{
	t_token				*tok;

	tok = token_alloc(TK_VEC);
	tok->num1 = ft_strtod(buf, (char **)&buf);
	buf++;
	tok->num2 = ft_strtod(buf, (char **)&buf);
	buf++;
	tok->num3 = ft_strtod(buf, (char **)&buf);
	*rest = buf;
	return (tok);
}

t_token	*tokenize(const char *buf)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (*buf)
	{
		if (consume_blank(&buf, buf))
			continue ;
		else if (is_identifier(buf))
			cur->next = identifier(&buf, buf);
		else if (is_number(buf))
			cur->next = number(&buf, buf);
		else if (is_vector(buf))
			cur->next = vector(&buf, buf);
		else if (consume_newline(&buf, buf))
			cur->next = token_alloc(TK_NL);
		else
			fatal_error("tokenize", "Unexpected character while tokenizing");
		cur = cur->next;
	}
	cur->next = token_alloc(TK_EOF);
	return (head.next);
}
