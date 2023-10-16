#include <stdio.h>
# include "get_next_line.h"

int main(void)
{
	char *line = 0;
	while (get_next_line(0, &line))
	{
		printf("%s\n", line);
	}
}
