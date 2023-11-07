#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	(void)argc;

	char *line = 0;
	unsigned int line_size = 0;

	int fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line, &line_size))
	{
		printf("%s", line);
		free(line);
		line = 0;
	}
	// printf("%s\n", line);
	// free(line);
}
