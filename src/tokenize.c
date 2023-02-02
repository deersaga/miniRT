#include "minirt.h"
#include "tokenize.h"
#include <string.h>
#include <ctype.h>

t_token	*token_alloc(t_token_type type)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	tok->type = type;
	return (tok);
}

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

// Identifier
bool	is_identifier(const char *s)
{
	static const char	*identifiers[] = {"A", "C", "L", "sp"};
	size_t				i;

	i = 0;
	while (i < sizeof(identifiers) / sizeof(*identifiers))
	{
		if (!memcmp(s, identifiers[i], strlen(identifiers[i])))
			return (true);
	}
	return (false);
}

t_token	*identifier(const char **rest, const char *buf)
{
	t_token				*tok;

	tok = token_alloc(TK_ID);
	if (!memcmp(buf, "A", 1))
	{
		tok->id = E_AMBIENT_LIGHTNING;
		buf++;
	}
	else if (!memcmp(buf, "C", 1))
	{
		tok->id = E_CAMERA;
		buf++;
	}
	else if (!memcmp(buf, "L", 1))
	{
		tok->id = E_LIGHT;
		buf++;
	}
	else if (!memcmp(buf, "sp", 2))
	{
		tok->id = E_SPHERE;
		buf += 2;
	}
	*rest = buf;
	return (tok);
}

// Number
// 1xxx
// .1xxx
bool	consume_number(const char **rest, const char *s)
{
	bool	seen_dot;

	if (isdigit(*s) || (*s == '.' && isdigit(s[1])))
	{
		seen_dot = false;
		while (*s && (isdigit(*s) || *s == '.'))
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

bool	is_number(const char *s)
{
	if (!consume_number(&s, s))
		return (false);
	if (*s == ' ' || *s == '\0')
		return (true);
	return (false);
}

t_token	*number(const char **rest, const char *s)
{
	const char	*start = s;
	t_token	*tok;

	tok = token_alloc(TK_NUM);
	while (*s && (isdigit(*s) || *s == '.'))
		s++;
	tok->num1 = atof(start);
	*rest = s;
	return (tok);
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
	if (*s != ' ' && *s != '\0')
		return (false);
	return (true);
}

t_token	*vector(const char **rest, const char *buf)
{
	*rest = buf;
	return (NULL);
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
			cur = cur->next = identifier(&buf, buf);
		else if (is_number(buf))
			cur = cur->next = number(&buf, buf);
		else if (is_vector(buf))
			cur = cur->next = vector(&buf, buf);
		else
			fatal_error("tokenize", "Unexpected character while tokenizing");
	}
	return (head.next);
}
