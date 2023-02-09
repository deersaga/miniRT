/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/09 21:29:54 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <float.h> // FLT_EPSILON
#include "minirt.h"
#include "tokenize.h"
#include "parse.h"

void	expect_once(t_element_type type)
{
	static bool	has_seen_ambient = false;
	static bool	has_seen_light = false;
	static bool	has_seen_camera = false;

	if (type == E_AMBIENT_LIGHTNING)
	{
		if (has_seen_ambient)
			fatal_error("expect_once", "A can only be declared once.");
		has_seen_ambient = true;
	}
	else if (type == E_LIGHT)
	{
		if (has_seen_light)
			fatal_error("expect_once", "L can only be declared once.");
		has_seen_light = true;
	}
	else if (type == E_CAMERA)
	{
		if (has_seen_camera)
			fatal_error("expect_once", "C can only be declared once.");
		has_seen_camera = true;
	}
	else
		fatal_error("expect_once", "Unexpected type");
}

static char	*read_all_content(const char *filename)
{
	int		fd;
	size_t	rc;
	char	buf[1000];
	char	*ret;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		fatal_error("open file", NULL);
	ret = ft_calloc(1, 1);
	while (1)
	{
		rc = read(fd, buf, 999);
		if (rc == 0)
			break ;
		buf[rc] = '\0';
		temp = ft_strjoin(ret, buf);
		if (temp == NULL)
			fatal_error("strjoin", "malloc error");
		free(ret);
		ret = temp;
	}
	close(fd);
	return (ret);
}

t_element	*parse(int argc, const char *argv[])
{
	char			*tail;
	char			*content;
	t_token			*tok;
	t_element		*elements;

	errno = 0;
	if (argc != 2)
		fatal_error("parse", "[Usage]: ./miniRT config_file");
	tail = ft_strrchr(argv[1], '.');
	if (tail == NULL || ft_strncmp(tail, ".rt", 4))
		fatal_error("parse", "extension must be .rt");
	content = read_all_content(argv[1]);
	tok = tokenize(content);
	free(content);
	elements = elementize(tok);
	free_tok(tok);
	return (elements);
}
