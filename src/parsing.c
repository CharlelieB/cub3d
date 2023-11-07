#include "cub3D.h"
#include "parsing.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include <stdbool.h>

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


/*test

printf("Height of the map : %d, Max width : %d\n", game->map_h, game->map_w);
	for (unsigned int k = 0; k < game->map_h; k++)
	{
		unsigned int l;
		for (l = 0; l < game->map_w; l++)
			printf("%c", game->map[k * game->map_w + l]);
		printf("\n");
	}
*/

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
	game->map_h = parsing->map_h;
	game->map_w = parsing->map_max_w;
	free_map(parsing->map, parsing->map_h);
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

void	free_stack_array_ptr(char *array[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(array[i]);
}

bool	map_assets_save(int fd, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->line = 0;
	parsing->lsize = 0;
	while (i < 6 && get_next_line(fd, &parsing->line, &parsing->lsize))
	{
		if (!is_empty(parsing->line))
		{
			parsing->assets[i] = malloc(parsing->lsize + 1);
			if (!parsing->assets[i])
				return (free(parsing->line), free_stack_array_ptr(parsing->assets, i), false);
			ft_strlcpy(parsing->assets[i], parsing->line, parsing->lsize + 1);
			++i;
		}
		free(parsing->line);
		parsing->line = 0;
	}
	if (i != 6)
		return (write(2, "Error\nMissing assets\n", 23), false);
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
			return (free(parsing->line), free_map(parsing->map, parsing->map_h), false);
		ft_strlcpy(*(parsing->map + parsing->map_h), parsing->line, parsing->lsize + 1);
		if (parsing->lsize > parsing->map_max_w)
			parsing->map_max_w = parsing->lsize;
		free(parsing->line);
		parsing->line = 0;
		++parsing->map_h;
	}
	return (true);
}

bool	map_parse(int fd, t_parsing *parsing, t_game *game)
{
	if (!map_assets_save(fd, parsing))
		return (false);
	if (!map_check_assets(parsing, game))
		return (free_stack_array_ptr(parsing->assets, 6), false);
	if (!map_save(fd, parsing))
		return (free_stack_array_ptr(parsing->assets, 6), false);
	if (!map_edit(parsing, game))
		return (free(game->map), false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_game		game;
	int			fd;

	if (argc != 2)
	{
		write(2, "Error\nPlease provide one argument\n", 36);
		return (-1);
	}
	map_check_format(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		write(2, "Error\nCould't open map file\n", 30);
	if (!map_parse(fd, &parsing, &game))
		return (close(fd), -1);
	close(fd);
	printf("game_exec\n");
	free(game.map);
	free_stack_array_ptr(parsing.assets, 6);
	// parse(map);
	return (0);
}
