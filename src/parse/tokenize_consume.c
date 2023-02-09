/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_consume.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:04 by katakagi          #+#    #+#             */
/*   Updated: 2023/02/10 02:52:31 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minirt.h"
#include "tokenize.h"

// Blank
bool	consume_blank(const char **rest, const char *buff)
{
	bool	consumed;

	consumed = false;
	while (*buff == ' ')
	{
		buff++;
		consumed = true;
	}
	*rest = buff;
	return (consumed);
}

// Number
// 1xxx
// .1xxx
bool	consume_number(const char **rest, const char *s)
{
	bool	seen_dot;

	if (*s == '+' || *s == '-')
		s++;
	if (ft_isdigit(*s) || (*s == '.' && ft_isdigit(s[1])))
	{
		seen_dot = false;
		while (*s && (ft_isdigit(*s) || *s == '.'))
		{
			if (*s == '.')
			{
				if (seen_dot)
					return (false);
				seen_dot = true;
			}
			s++;
		}
		*rest = s;
		return (true);
	}
	else
		return (false);
}

// Vector
bool	consume_comma(const char **rest, const char *s)
{
	if (*s == ',')
	{
		s++;
		*rest = s;
		return (true);
	}
	return (false);
}

// A 0.2 255,255,255
// ^ ^   ^  ^^  ^^

bool	consume_newline(const char **rest, const char *buf)
{
	if (*buf != '\n')
		return (false);
	*rest = buf + 1;
	return (true);
}
