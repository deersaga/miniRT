/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/02 14:51:13 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "minirt.h"
#include "parse.h"

t_element	*sphere_element_alloc(t_vec center, FLOAT diameter, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_SPHERE;
	self->center = center;
	self->diameter = diameter;
	self->color = color;
	return (self);
}

t_element	*light_element_alloc(t_vec p, FLOAT ratio, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_LIGHT;
	self->light_point = p;
	self->light_brightness_ratio = ratio;
	self->color = color;
	return (self);
}

t_element	*camera_element_alloc(t_vec p, t_vec dir, FLOAT hfov)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_CAMERA;
	self->view_point = p;
	self->orientation_vec = dir;
	self->hfov = hfov;
	return (self);
}

t_element	*ambient_element_alloc(FLOAT ratio, t_color color)
{
	t_element	*self;

	self = calloc(1, sizeof(*self));
	if (self == NULL)
		fatal_error("parse", NULL);
	self->element_type = E_AMBIENT_LIGHTNING;
	self->ambient_lightning_ratio = ratio;
	self->color = color;
	return (self);
}

void	element_add(t_element *head, t_element *elem)
{
	while (head->next)
	{
		head = head->next;
	}
	head->next = elem;
}

bool	consume_blank(char **rest, char *buff)
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

bool	is_number(const char *s)
{
	if (!isdigit(*s))
		return (true);
	return (false);
}



void	tokenize(char *buff, t_token *head)
{
	size_t	i;

	i = 0;
	while (*buff)
	{
		if (consume_blank(&buff, buff))
			continue ;
		
	}
}


t_element	*parse(int argc, const char *argv[])
{
	t_element	head;
	int			fd;
	char		*tail;
	char		buff[1000];
	t_token		head;

	errno = 0;
	if (argc != 2)
		fatal_error("parse", "[Usage]: ./miniRT config_file");
	tail = strrchr(argv[1], '.');
	if (tail == NULL || strcmp(tail, ".rt"))
		fatal_error("parse", "extension must be .rt");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fatal_error("parse", NULL);
	read(fd, buff, 999);
	buff[999] = '\0';
	tokenize(&buff, &head);
	close(fd);
	head.next = NULL;
	element_add(&head, ambient_element_alloc(0.1, color_new(255, 255, 255)));
	element_add(&head, camera_element_alloc(vec_new(-50, 10, 20), vec_new(1, 0, 0), 70));
	element_add(&head, sphere_element_alloc(point_new(0, 12.6, 20.6), 12.6, color_new(10, 0, 255)));
	element_add(&head, sphere_element_alloc(point_new(0, -500, 20), 500, color_new(255, 0, 255)));
	element_add(&head, light_element_alloc(point_new(-40, 50.0, 20.0), 0.6, color_new(255, 255, 255)));
	return (head.next);
}
