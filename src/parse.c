#include <fcntl.h>
#include "minirt.h"

int	parse(int argc, const char *argv[], t_scene *scene)
{
	int	fd;

	(void)scene;
	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	return (0);
}
