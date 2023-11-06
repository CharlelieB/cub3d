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
	while (i < parsing->map_h)
	{
		*(new_map + i) = *(parsing->map + i);
		++i;
	}
	free(parsing->map);
	parsing->map = new_map;
	return (true);
}

// Remove \n from map, add empty spaces to get a rectangle map

bool	map_edit(t_parsing *parsing, t_game *game)
{
	int				i;
	unsigned int	j;

	i = -1;
	game->map = malloc((--parsing->map_max_w) * parsing->map_h);
	if (!game->map)
	{
		write(2, "Map allocation failed\n", 23);
		return (free_map(parsing->map, parsing->map_h), false);
	}
	while (++i < parsing->map_h)
	{
		j = 0;
		while (parsing->map[i][j] && parsing->map[i][j] != '\n')
		{
			(game->map)[i * parsing->map_max_w + j] = parsing->map[i][j];
			++j;
		}
		while (j < parsing->map_max_w)
			(game->map)[i * parsing->map_max_w + j++] = 32;
	}
	free_map(parsing->map, parsing->map_h);
	game->map_h = parsing->map_h;
	game->map_w = parsing->map_max_w;
	printf("Height of the map : %d, Max width : %d\n", game->map_h, game->map_w);
	for (unsigned int k = 0; k < game->map_h; k++)
	{
		unsigned int l;
		for (l = 0; l < game->map_w; l++)
			printf("%c", game->map[k * game->map_w + l]);
		printf("\n");
	}
	return (true);
}

bool	map_save(int fd, t_parsing *parsing)
{
	parsing->map_h = 0;
	parsing->map_max_w = 0;
	parsing->line = 0;
	parsing->lsize = 0;
	parsing->alloc_size = 32;
	parsing->map = malloc(sizeof(char *) * parsing->alloc_size);
	if (!parsing->map)
	{
		write(2, "Map allocation failed\n", 23);
		return (false);
	}
	while (get_next_line(fd, &parsing->line, &parsing->lsize))
	{
		if (parsing->map_h > parsing->alloc_size)
			if (!ft_realloc(parsing))
				return (free(parsing->line), false);
		*(parsing->map + parsing->map_h) = malloc(parsing->lsize + 1);
		if (!*(parsing->map + parsing->map_h))
			return (free_map(parsing->map, parsing->map_h), false);
		//printf("%p\n", *(parsing->map + parsing->map_h));
		ft_strlcpy(*(parsing->map + parsing->map_h), parsing->line, parsing->lsize + 1);
		if (parsing->lsize > parsing->map_max_w)
			parsing->map_max_w = parsing->lsize;
		free(parsing->line);
		parsing->line = 0;
		++parsing->map_h;
	}
	return (true);
}

bool	map_parse(char *filename, t_parsing *parsing, t_game *game)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		if (map_save(fd, parsing))
		{
			close(fd);
			if (map_edit(parsing, game))
				return (true);
			return (false);
		}
		return (close(fd), false);
	}
	perror("Couldn't open map");
	return (false);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_game		game;

	if (argc != 2)
	{
		write(2, "Not enough argument\n", 20);
		return (-1);
	}
	map_check_format(argv[1]);
	if (!map_parse(argv[1], &parsing, &game))
		return (1);
	
	// parse(map);
	return (0);
}
