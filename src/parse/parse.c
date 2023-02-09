/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/10 02:52:21 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"
#include <fcntl.h>
#include <errno.h>

static char	*read_all_content(const char *filename)
{
	int		fd;
	size_t	rc;
	char	buf[1000];
	char	*ret;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		fatal_error("read_all_content", "open file error");
	ret = ft_calloc(1, 1);
	while (1)
	{
		rc = read(fd, buf, 999);
		if (rc == 0)
			break ;
		buf[rc] = '\0';
		temp = ft_strjoin(ret, buf);
		if (temp == NULL)
			fatal_error("read_all_content", "strjoin error");
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
