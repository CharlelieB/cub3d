#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int	main(int argc, char **argv)
{
	(void)argc;
	printf("%u\n", next_power(0));
	char *line = NULL;
	int fd;
	char **map;

	fd = open(argv[1], O_RONLY);
	if (fd == -1)
		write(2, "cannot open file\n", 17);
	while (get_next_line(fd, &line))
	{

		++(*map) = malloc(sizeof(line));
		strdup 
		free(line);
	}
	return (0);
}
