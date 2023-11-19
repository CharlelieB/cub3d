#include "cub3D.h"

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

