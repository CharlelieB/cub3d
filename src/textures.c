/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:46:58 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/07 17:17:00 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

char	textures_get_id(t_data *data)
{
	if (data->side == 0 && data->ray.x > 0)
		return (SO);
	else if (data->side == 1 && data->ray.y > 0)
		return (EA);
	else if (data->side == 1 && data->ray.y < 0)
		return (WE);
	return (0);
}

int	textures_get_x(t_game *game, t_data *data, int id)
{
	float	wall_x;
	int		tex_x;

	if (data->side == 0)
		wall_x = game->ppos.y + data->wall_dist * data->ray.y;
	else
		wall_x = game->ppos.x + data->wall_dist * data->ray.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)game->mlx->textures[id].width);
	if ((data->side == 0 && data->ray.x > 0) || (data->side == 1
			&& data->ray.y < 0))
			tex_x = game->mlx->textures[id].width - tex_x - 1;
	return (tex_x);
}

void	textures_draw(t_game *game, t_data *data, int start, int end)
{
	float	step;
	int		tex_id;
	float	tex_pos;
	int		y;
	int		texture_w;

	tex_id = textures_get_id(data);
	data->tex_x = textures_get_x(game, data, tex_id);
	step = 1.0f * game->mlx->textures[tex_id].width / data->wall_height;
	tex_pos = (start - SCREEN_H_HALF + (data->wall_height >> 1)) * step;
	texture_w = game->mlx->textures[tex_id].line_len;
	y = start;
	while (y < end)
	{
		data->tex_y = (int)tex_pos & (game->mlx->textures[tex_id].height - 1);
		tex_pos += step;
		ft_pixel_put(&game->mlx->img, data->screen_x, y,
			*(unsigned int *)(game->mlx->textures[tex_id].addr
				+ texture_w * data->tex_y + data->tex_x * 4));
		++y;
	}
}
