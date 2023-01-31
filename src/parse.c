#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "minirt.h"

t_scene	parse(int argc, const char *argv[])
{
	t_scene	scene;
	int	fd;
	char	*tail;

	scene = (t_scene){};
	errno = 0;
	if (argc != 2)
		fatal_error("parse", "[Usage]: ./miniRT config_file");
	tail = strrchr(argv[1], '.');
	if (tail == NULL || strcmp(tail, ".rt"))
		fatal_error("parse", "extension must be .rt");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fatal_error("parse", NULL);
	
	return (scene);
}
