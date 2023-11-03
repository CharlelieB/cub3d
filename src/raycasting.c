#include "cub3D.h"

#include <math.h>
#include <float.h>

void	draw_walls(t_game *game, t_data *data, int x)
{
	float	wall_dist;
	int 	line_height;
	int 	draw_start;
	int 	draw_end;

	if(data->side == 0)
		wall_dist = ft_fabs(data->side_x - data->delta_x);
    else
		wall_dist = ft_fabs(data->side_y - data->delta_y);
	if (wall_dist)
		line_height = ft_abs((int)(SCREEN_H / wall_dist));
	else
		line_height = INFINITY;
	draw_start = -line_height / 2 + SCREEN_H_HALF;
    if(draw_start < 0)
		draw_start = 0;
    draw_end = line_height / 2 + SCREEN_H_HALF;
    if(draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	int color = 0x232323;
	if (data->side == 1)
		color = 0x5f5f5f;
	int count = draw_end - draw_start;
	// draw_textures();
	for (int i = 0; i < count; i++)
	{
		ft_pixel_put(&game->mlx->img, x, draw_start, color);
		++draw_start;
	}
}

void	dda_init(t_game *game, t_data *data)
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
		data->side_x = (game->ppos.x - (t_f) data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->side_x = ((t_f) data->map_x + 1.0 - game->ppos.x) * data->delta_x;
	}
	if (data->ray.y < 0)
	{
		data->step_y = -1;
		data->side_y = (game->ppos.y - (t_f) data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->side_y = ((t_f) data->map_y + 1.0 - game->ppos.y) * data->delta_y;
	}
}

void	ray_loop(t_data *data)
{
	int		hit;

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

void	raycasting(t_game *game, int x)
{
	t_data	data;
	float camera_x = 2 * x / (float)SCREEN_W - 1;

	data.ray.x = game->pdir.x + game->plane.x * camera_x;
	data.ray.y = game->pdir.y + game->plane.y * camera_x;
	data.map_x = (int)game->ppos.x;
	data.map_y = (int)game->ppos.y;
	dda_init(game, &data);
	ray_loop(&data);
	draw_walls(game, &data, x);
}
