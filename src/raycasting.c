#include "cub3D.h"

#include <math.h>
#include <float.h>

void draw_textures(t_game *game, t_data *data, int start, int end)
{
	int 	text_id = 0;
	float 	wall_x;
	int 	tex_x;

	if (data->side == 0 && data->ray.x > 0)
		text_id = 1;
	if (data->side == 0)
		wall_x = game->ppos.y + data->wall_dist * data->ray.y;
	else
		wall_x = game->ppos.x + data->wall_dist * data->ray.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)TEX_W);
	if ((data->side == 0 && data->ray.x > 0) || (data->side == 1 && data->ray.y < 0))
		tex_x = TEX_W - tex_x - 1;
	float	step = 1.0f * TEX_H / data->wall_height;
	float	tex_pos = (start - SCREEN_H_HALF + data->wall_height / 2) * step;
	int texture_w = game->mlx->textures[text_id].line_len;
	for (int y = start; y < end; ++y)
	{
		int tex_y = (int)tex_pos & (TEX_H - 1);
		tex_pos += step;
		int color = *(unsigned int *)(game->mlx->textures[text_id].addr + texture_w * tex_y + tex_x * 4);
		ft_pixel_put(&game->mlx->img, data->screen_x, y, color);
	}
}

void draw_walls(t_game *game, t_data *data)
{
	int start;
	int end;

	if (data->side == 0)
		data->wall_dist = ft_fabs(data->side_x - data->delta_x);
	else
		data->wall_dist = ft_fabs(data->side_y - data->delta_y);
	if (data->wall_dist)
		data->wall_height = ft_abs((int)(SCREEN_H / data->wall_dist));
	else
		data->wall_height = INFINITY;
	start = -data->wall_height / 2 + SCREEN_H_HALF;
	if (start < 0)
		start = 0;
	end = data->wall_height / 2 + SCREEN_H_HALF;
	if (end >= SCREEN_H)
		end = SCREEN_H - 1;
	draw_textures(game, data, start, end);
	// int color = 0x232323;
	// if (data->side == 1)
	// 	color = 0x5f5f5f;
	// int count = draw_end - draw_start;

	// for (int i = 0; i < count; i++)
	// {
	// 	ft_pixel_put(&game->mlx->img, x, draw_start, color);
	// 	++draw_start;
	// }
}

void dda_init(t_game *game, t_data *data)
{
	if (data->ray.x == 0)
		data->delta_x = 1.0e30f;
	else
		data->delta_x = ft_fabs(1 / data->ray.x);
	if (data->ray.y == 0)
		data->delta_y = 1.0e30f;
	else
		data->delta_y = ft_fabs(1 / data->ray.y);
	if (data->ray.x < 0)
	{
		data->step_x = -1;
		data->side_x = (game->ppos.x - (t_f)data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->side_x = ((t_f)data->map_x + 1.0 - game->ppos.x) * data->delta_x;
	}
	if (data->ray.y < 0)
	{
		data->step_y = -1;
		data->side_y = (game->ppos.y - (t_f)data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->side_y = ((t_f)data->map_y + 1.0 - game->ppos.y) * data->delta_y;
	}
}

void ray_loop(t_data *data)
{
	int hit;

	hit = 0;
	while (hit == 0)
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
		if (map[data->map_x + (data->map_y * MAP_W)] == 1)
			hit = 1;
	}
}

void raycasting(t_game *game, int x)
{
	t_data data;
	float camera_x = 2 * x / (float)SCREEN_W - 1;

	data.screen_x = x;
	data.ray.x = game->pdir.x + game->plane.x * camera_x;
	data.ray.y = game->pdir.y + game->plane.y * camera_x;
	data.map_x = (int)game->ppos.x;
	data.map_y = (int)game->ppos.y;
	dda_init(game, &data);
	ray_loop(&data);
	draw_walls(game, &data);
}
