#include <fcntl.h>
#include <errno.h>
#include "minirt.h"

t_scene	parse(int argc, const char *argv[])
{
	t_scene	scene;
	int	fd;

	scene = (t_scene){};
	errno = 0;
	if (argc != 2)
		fatal_error("parse", "[Usage]: ./miniRT config_file");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fatal_error("parse", NULL);
	return (scene);
}
