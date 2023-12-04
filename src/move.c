#include "cub3D.h"
#include <math.h>

void	move_forward(t_game *game, float speed)
{
	// if ((game->ppos.x + game->pdir.x * speed) >= (float)(game->map_w - 1))
	// 	game->ppos.x = 2.5;
	// else if ((game->ppos.x + game->pdir.x * speed) <= 0.0)
	// 	game->ppos.x = (float)game->map_w - 2.5;
	// else
	float new_x;
	float new_y;

	new_x = game->ppos.x + game->pdir.x * speed;
	new_y = game->ppos.y + game->pdir.y * speed;
	if (new_x <= 0 || new_y <= 0
		|| new_x >= (float)(game->map_w - 1)
		|| new_y >= (float)(game->map_h - 1))
			return ;
	game->ppos.x = new_x;
	// if ((game->ppos.y + game->pdir.y * speed) >= (float)(game->map_h - 1))
	// 	game->ppos.y = 2.5;
	// else if ((game->ppos.y + game->pdir.y * speed) <= 0.0)
	// 	game->ppos.y = (float)game->map_h - 2.5;
	// else
	game->ppos.y = new_y;
}

void	move_backward(t_game *game, float speed)
{
	// if ((game->ppos.x + game->pdir.x * speed) >= (float)(game->map_w - 1))
	// 	game->ppos.x = 2.5;
	// else if ((game->ppos.x + game->pdir.x * speed) <= 0.0)
	// 	game->ppos.x = (float)game->map_w - 2.5;
	// else
	float new_x;
	float new_y;

	new_x = game->ppos.x - game->pdir.x * speed;
	new_y = game->ppos.y - game->pdir.y * speed;
	if (new_x <= 0 || new_y <= 0
		|| new_x >= (float)(game->map_w - 1)
		|| new_y >= (float)(game->map_h - 1))
			return ;
	game->ppos.x = new_x;
	// if ((game->ppos.y + game->pdir.y * speed) >= (float)(game->map_h - 1))
	// 	game->ppos.y = 2.5;
	// else if ((game->ppos.y + game->pdir.y * speed) <= 0.0)
	// 	game->ppos.y = (float)game->map_h - 2.5;
	//else
	game->ppos.y = new_y;
}

void	move_player(int key, t_game *game)
{
	float	speed;

	speed = 0.4;
	if (key == W)
		move_forward(game, speed);
	else if (key == S)
		move_backward(game, speed);
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}

void	move_direction(int key, t_game *game)
{
	float	old_x;
	float	old_plane_x;

	old_x = game->pdir.x;
	old_plane_x = game->plane.x;
	if (key == D)
	{
		game->pdir.x = old_x * cos(game->rot) - game->pdir.y * sin(game->rot);
		game->pdir.y = old_x * sin(game->rot) + game->pdir.y * cos(game->rot);
		game->plane.x = old_plane_x * cos(game->rot) - game->plane.y * sin(game->rot);
		game->plane.y = old_plane_x * sin(game->rot) + game->plane.y * cos(game->rot);
	}
	else if (key == A)
	{
		game->pdir.x = old_x * cos(-game->rot) - game->pdir.y * sin(-game->rot);
		game->pdir.y = old_x * sin(-game->rot) + game->pdir.y * cos(-game->rot);
		game->plane.x = old_plane_x * cos(-game->rot) - game->plane.y * sin(-game->rot);
		game->plane.y = old_plane_x * sin(-game->rot) + game->plane.y * cos(-game->rot);
	}
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}
