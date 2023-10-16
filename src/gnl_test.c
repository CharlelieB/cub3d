#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	char *line = 0;
	unsigned int		l_size = 0;

	while (get_next_line(0, &line, &l_size))
	{
		printf("%d\n", l_size);
		printf("%s\n", line);
	}
}
