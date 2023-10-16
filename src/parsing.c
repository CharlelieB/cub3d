#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	(void)argc;

	char *line = 0;
	unsigned lsize = 0;
	int fd;
	char **map;
	int	i = 0;
	int	alloc_s = 32;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		write(2, "cannot open file\n", 17);
	map = malloc(sizeof(char *) * alloc_s);
	if (!map)
		return 1;

	while (get_next_line(fd, &line, &lsize))
	{
		// if (i > alloc_s)
		// {
		// 	alloc_s = ft_next_power(alloc_s);
		// 	map = malloc(sizeof(char *) * alloc_s);
		// }

		*(map + i) = malloc(lsize);
		if (*map == 0)
			return (0);
		ft_strlcpy(*(map + i), line, lsize);
		free(line);
		line = 0;
		++i;
	}
	for (int j = 0; j < i; j++)
	{
		printf("%s\n", map[j]);
		free(map[j]);
	}
	close(fd);
	return (0);
}
