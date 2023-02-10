/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:57:58 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 03:41:53 by katakagi         ###   ########.fr       */
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
