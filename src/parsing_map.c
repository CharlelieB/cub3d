/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:34:47 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/06 12:53:14 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

bool	flood_fill(t_game *game, int x, int y)
{
	int	index;

	index = x + y * game->map_w;
	if (game->map[index] == '1' || game->map[index] == '2')
		return (true);
	if (x == 0 || x == (int)game->map_w - 1
		|| y == 0 || y == (int)game->map_h - 1)
		return (false);
	game->map[index] = '2';
	if (game->map[index] == 32)
		return (false);
	if (!flood_fill(game, x + 1, y))
		return (false);
	if (!flood_fill(game, x, y + 1))
		return (false);
	if (!flood_fill(game, x - 1, y))
		return (false);
	if (!flood_fill(game, x, y - 1))
		return (false);
	return (true);
}

void	setup_player(char c, t_game *game, int y, int x)
{
	game->ppos.x = x + 0.5;
	game->ppos.y = y + 0.5;
	game->pdir.y = 0;
	game->pdir.x = 0;
	if (c == 'N')
		game->pdir.y = 1;
	else if (c == 'S')
		game->pdir.y = -1;
	else if (c == 'W')
		game->pdir.x = -1;
	else if (c == 'E')
		game->pdir.x = 1;
	if (!game->pdir.y)
	{
		game->plane.x = 0;
		game->plane.y = 0.66;
	}
	else
	{
		game->plane.x = 0.66;
		game->plane.y = 0;
	}
}

bool	map_char_checker(t_parsing *parsing, t_game *game, int i, int j)
{
	char	c;

	c = parsing->map[i][j];
	if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
	{
		if (parsing->player_found)
		{
			write(2, "Error\nMore than one player\n", 27);
			return (false);
		}
		else
			parsing->player_found = true;
		return (setup_player(c, game, i, j), true);
	}
	if (!is_space(c) && c != '0' && c != '1')
	{
		write(2, "Error\nInvalid character\n", 24);
		return (false);
	}
	return (true);
}

bool	map_fill(t_parsing *parsing, t_game *game)
{
	int				i;
	unsigned int	j;

	i = 0;
	while (i < parsing->map_h)
	{
		j = 0;
		while (parsing->map[i][j] && parsing->map[i][j] != '\n')
		{
			if (!map_char_checker(parsing, game, i, j))
				return (false);
			(game->map)[i * parsing->map_max_w + j] = parsing->map[i][j];
			++j;
		}
		while (j < parsing->map_max_w)
			(game->map)[i * parsing->map_max_w + j++] = 32;
		++i;
	}
	return (true);
}

bool	map_edit(t_parsing *parsing, t_game *game)
{
	game->map = malloc((--parsing->map_max_w) * parsing->map_h);
	if (!game->map)
	{
		write(2, "Map allocation failed\n", 22);
		free_map(parsing->map, parsing->map_h);
		return (false);
	}
	if (!map_fill(parsing, game))
	{
		free_map(parsing->map, parsing->map_h);
		return (false);
	}
	if (!parsing->player_found)
		return (write(2, "Error\nNo player\n", 16), false);
	game->map_h = parsing->map_h;
	game->map_w = parsing->map_max_w;
	game->map_s = game->map_h * game->map_w;
	return (free_map(parsing->map, parsing->map_h), true);
}
