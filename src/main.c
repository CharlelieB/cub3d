/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:32:12 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/06 13:21:45 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	destroyer(t_game *game, t_parsing *parsing)
{
	if (game->map)
		free(game->map);
	free_stack_array_ptr(parsing->assets, 6);
}

void	init(t_game *game, t_parsing *parsing)
{
	game->map = 0;
	ft_bzero(parsing->assets, 0);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing;
	t_game		game;
	int			fd;

	if (argc != 2)
	{
		write(2, "Error\nPlease provide one argument\n", 34);
		return (-1);
	}
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		return (close(fd), write(2, "Error\nMap is a directory\n", 25), -1);
	init(&game, &parsing);
	map_check_format(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		write(2, "Error\nCould't open map file\n", 28);
	if (map_parse(fd, &parsing, &game))
		game_loop(&game);
	close(fd);
	destroyer(&game, &parsing);
	return (0);
}
