/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:26:43 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 16:26:02 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	move_forward(t_game *game, float speed)
{
	float	new_x;
	float	new_y;

	new_x = game->ppos.x + game->pdir.x * speed;
	new_y = game->ppos.y + game->pdir.y * speed;
	if (new_x <= 0 || new_y <= 0
		|| new_x >= (float)(game->map_w - 1)
		|| new_y >= (float)(game->map_h - 1))
		return ;
	game->ppos.x = new_x;
	game->ppos.y = new_y;
}

void	move_backward(t_game *game, float speed)
{
	float	new_x;
	float	new_y;

	new_x = game->ppos.x - game->pdir.x * speed;
	new_y = game->ppos.y - game->pdir.y * speed;
	if (new_x <= 0 || new_y <= 0
		|| new_x >= (float)(game->map_w - 1)
		|| new_y >= (float)(game->map_h - 1))
		return ;
	game->ppos.x = new_x;
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
	float	cos_rot;
	float	sin_rot;

	old_x = game->pdir.x;
	old_plane_x = game->plane.x;
	if (key == D)
	{
		cos_rot = cos(game->rot);
		sin_rot = sin(game->rot);
	}
	else
	{
		cos_rot = cos(-game->rot);
		sin_rot = sin(-game->rot);
	}
	game->pdir.x = old_x * cos_rot - game->pdir.y * sin_rot;
	game->pdir.y = old_x * sin_rot + game->pdir.y * cos_rot;
	game->plane.x = old_plane_x * cos_rot - game->plane.y * sin_rot;
	game->plane.y = old_plane_x * sin_rot + game->plane.y * cos_rot;
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}
