#include <stdio.h>
#include "libft.h"

int main(void)
{
	char line[255] = "salut ca    va?";
	t_str_array array;

	while (ft_split2(&array, line))
	{
		printf("%d\n", l_size);
		printf("%s\n", line);
	}
}
