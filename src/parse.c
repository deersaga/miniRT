/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakagi <katakagi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:31:52 by susami            #+#    #+#             */
/*   Updated: 2023/02/01 14:42:45 by katakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "minirt.h"

t_scene	parse(int argc, const char *argv[])
{
	t_scene	scene;
	int		fd;
	char	*tail;

	errno = 0;
	if (argc != 2)
		fatal_error("parse", "[Usage]: ./miniRT config_file");
	tail = strrchr(argv[1], '.');
	if (tail == NULL || strcmp(tail, ".rt"))
		fatal_error("parse", "extension must be .rt");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fatal_error("parse", NULL);
	close(fd);
	scene.camera = (t_camera){
		.eye_position = vec_new(-50, 0, 20),
		.look_at_direction = vec_new(1, 0, 0),
		.hfov = 70};
	scene.sphere = (t_sphere){
		.center = point_new(0, 0, 20.6),
		.radius = 12.6,
		.color = color_new(10, 0, 255),
	};
	scene.light_source = (t_light_source){
		.position = vec_new(-40, 50.0, 0.0),
		.ratio = 0.6,
		.color = color_new(255, 255, 255)
	};
	scene.ambient_intencity = color_new(0.5, 0.5, 0.5);
	return (scene);
}
