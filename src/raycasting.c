/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:12:58 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/07 19:51:03 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include <math.h>
#include <float.h>

void	walls_draw(t_game *game, t_data *data)
{
	int	start;
	int	end;

	if (data->side == 0)
		data->wall_dist = fabs(data->side_x - data->delta_x);
	else
		data->wall_dist = fabs(data->side_y - data->delta_y);
	if (data->wall_dist)
		data->wall_height = ft_abs((int)(SCREEN_H / data->wall_dist));
	else
		data->wall_height = INFINITY;
	start = -data->wall_height / 2 + SCREEN_H_HALF;
	if (start < 0)
		start = 0;
	end = (data->wall_height >> 1) + SCREEN_H_HALF;
	if (end >= SCREEN_H)
		end = SCREEN_H - 1;
	textures_draw(game, data, start, end);
}

bool	ray_loop(t_data *data, t_game *game)
{
	int	map_coord;

	while (true)
	{
		if (data->side_x < data->side_y)
		{
			data->side_x += data->delta_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_y += data->delta_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		map_coord = data->map_x + (data->map_y * game->map_w);
		if (data->map_x < 0 || data->map_x >= (int)game->map_w
			|| data->map_y < 0
			|| data->map_y >= (int)game->map_h)
			return (false);
		if (game->map[map_coord] == '1')
			break ;
	}
	return (true);
}

void	raycasting(t_data *data, t_game *game, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)SCREEN_W - 1;
	data->screen_x = x;
	data->ray.x = game->pdir.x + game->plane.x * camera_x;
	data->ray.y = game->pdir.y + game->plane.y * camera_x;
	data->map_x = (int)(game->ppos.x);
	data->map_y = (int)(game->ppos.y);
	dda_init(game, data);
	if (ray_loop(data, game))
		walls_draw(game, data);
}
