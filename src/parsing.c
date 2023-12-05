/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:56:50 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 16:25:34 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		write(2, "Error\nWrong file format\n", 24);
		exit(1);
	}
	i -= 4;
	if (ft_strncmp(filename + i, ".cub", 4))
	{
		write(2, "Error\nWrong file format\n", 24);
		exit(1);
	}
}

/*test to display map
printf("Height of the map : %d, Max width : %d\n", game->map_h, game->map_w);
	for (unsigned int k = 0; k < game->map_h; k++)
	{
		unsigned int l;
		for (l = 0; l < game->map_w; l++)
			printf("%c", game->map[k * game->map_w + l]);
		printf("\n");
	}
*/

// Remove \n from map, add empty spaces to get a rectangle map

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
				return (free(parsing->line),
					free_stack_array_ptr(parsing->assets, i), false);
			ft_strlcpy(parsing->assets[i], parsing->line, parsing->lsize + 1);
			++i;
		}
		free(parsing->line);
		parsing->line = 0;
	}
	if (i != 6)
		return (write(2, "Error\nMissing assets\n", 21), false);
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
		return (write(2, "Map allocation failed\n", 22), false);
	while (get_next_line(fd, &parsing->line, &parsing->lsize))
	{
		if (parsing->map_h > parsing->alloc_size)
			if (!ft_realloc(parsing))
				return (free(parsing->line), false);
		*(parsing->map + parsing->map_h) = malloc(parsing->lsize + 1);
		if (!*(parsing->map + parsing->map_h))
			return (free(parsing->line),
				free_map(parsing->map, parsing->map_h), false);
		ft_strlcpy(*(parsing->map + parsing->map_h++),
			parsing->line, parsing->lsize + 1);
		if (parsing->lsize > parsing->map_max_w)
			parsing->map_max_w = parsing->lsize;
		free(parsing->line);
		parsing->line = 0;
	}
	return (true);
}

bool	map_parse(int fd, t_parsing *parsing, t_game *game)
{
	parsing->player_found = false;
	if (!map_assets_save(fd, parsing))
		return (false);
	if (!map_check_assets(parsing, game))
		return (free_stack_array_ptr(parsing->assets, 6), false);
	if (!map_save(fd, parsing))
		return (free_stack_array_ptr(parsing->assets, 6), false);
	if (!map_edit(parsing, game))
		return (free(game->map), false);
	if (!flood_fill(game, game->ppos.x, game->ppos.y))
		return (write(2, "Error\nMap format\n", 17), false);
	return (true);
}
