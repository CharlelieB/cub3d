#include "cub3D.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include <stdbool.h>

// static const char *direction[] = 
// {
// 	"NO",
// 	"SO",
// 	"WE",
// 	"EA",
// 	"F",
// 	"C"
// };

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_empty(char *str)
{
	while (*str)
	{
		if (*str != '\n' && !is_space(*str))
			return (false);
		++str;
	}
	return (true);
}

// bool	parse(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 6)
// 	{
// 		while (is_empty(map[i]))
// 			*(++map);
// 		while (is_space(*(map[i])))
// 			++(map[i]);
// 		j = 0;
// 		while (j < 6)
// 		{
// 			if (ft_strncmp(map))
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	map_check_format(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		++i;
	if (i < 5)
	{
		write(2, "Wrong file format\n", 19);
		exit(1);
	}
	i -= 4;
	if (ft_strncmp(filename + i, ".cub", 4))
	{
		write(2, "Wrong file format\n", 19);
		exit(1);
	}
}

void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(*(map + i));
		++i;
	}
	free(map);
}

bool	ft_realloc(t_parsing *parsing)
{
	char	**new_map;
	int				i;

	i = 0;
	parsing->alloc_size = ft_next_power(parsing->alloc_size);
	new_map = malloc(parsing->alloc_size);
	if (!new_map)
	{
		write(2, "Failed to realloc\n", 17);
		free_map(parsing->map, parsing->map_h);
		return (false);
	}

	return (true);
}



bool	map_save(int fd, t_parsing *parsing)
{
	parsing->map_h = 0;
	parsing->line = 0;
	parsing->lsize;
	parsing->alloc_size = 32;
	parsing->map = malloc(sizeof(char *) * parsing->alloc_size);
	if (!parsing->map)
	{
		write(2, "Map allocation failed\n", 23);
		return (false);
	}
	while (get_next_line(fd, &parsing->line, &parsing->lsize))
	{
		// if (i > alloc_s)
		// {
		// 	alloc_s = ft_next_power(alloc_s);
		// 	map = malloc(sizeof(char *) * alloc_s);
		// }
		if (parsing->map_h > parsing->alloc_size)
			if (!ft_realloc(parsing))
				return (free(parsing->line), false);
		ft_strlcpy(*(map + i), line, lsize);
		free(line);
		line = 0;
		++parsing->map_h;
	}
	for (int j = 0; j < parsing->map_h; j++)
	{
		printf("%s\n", map[j]);
		free(map[j]);
	}
}

void	map_parse(char *filename, t_parsing *parsing)
{
	int fd;

	fd = open(filename[1], O_RDONLY);
	if (fd == -1)
		perror("Couldn't open map");
	map_save(fd, parsing);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_parsing parsing;

	if (argc != 2)
	{
		write(2, "Not enough argument\n", 20);
		return (-1);
	}
	map_check_format(argv[1]);
	map_parse(argv[1], &parsing);
	
	// parse(map);
	return (0);
}
