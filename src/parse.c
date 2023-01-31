#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "minirt.h"
#include "get_next_line.h"

t_scene	parse(int argc, const char *argv[])
{
	t_scene	scene;
	int	fd;
	char	*tail;
	char	*line;

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
	line = get_next_line(fd);
	while (line)
	{
		if (!strcmp(line, "A 0.2 255,255,255\n"))
			;
		else if (!strcmp(line, "C  -50.0,0,20 0,0,1 70\n"))
			;
		else if (!strcmp(line, "sp 0.0,0.0,20.6 12.6 10,0,255\n"))
			;
		else
			fatal_error("parse", line);
		line = get_next_line(fd);
	}

	return (scene);
}

