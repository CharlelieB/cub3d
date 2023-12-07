#include "cub3D.h"

void	floor_casting(t_data *data, t_game *game, int y)
{
	float	p;
	float	row_distance;
	float	step_y;
	float	step_x;
	float	floor_x;
	float	floor_y;

	data->ray_dir_x1 = game->pdir.x - game->plane.x;
	data->ray_dir_x2 = game->pdir.x + game->plane.x;
	data->ray_dir_y1 = game->pdir.y - game->plane.y;
	data->ray_dir_y2 = game->pdir.y + game->plane.y;

	p = y - SCREEN_H_HALF;
	//distance of each floor row to camera
	row_distance = SCREEN_H_HALF / p;
	//real world step vector to add to each x  
	step_x = row_distance * (data->ray_dir_x2 - data->ray_dir_x1) / SCREEN_W;
	step_y = row_distance * (data->ray_dir_y2 - data->ray_dir_y1) / SCREEN_W;
	//world coord of the left most col (start)
	floor_x = game->ppos.x + row_distance * (data->ray_dir_x1);
	floor_y = game->ppos.y + row_distance * (data->ray_dir_y1);

	for (int x = 0; x < SCREEN_W; ++x)
	{
		int	cell_x = (int)floor_x;
		int	cell_y = (int)floor_y;
	
		int	tex_x = (int)(game->mlx->textures[0].width * (floor_x - cell_x)) & (game->mlx->textures[0].width - 1);
		int	tex_y = (int)(game->mlx->textures[0].height * (floor_y - cell_y)) & (game->mlx->textures[0].height - 1);
	
		floor_x += step_x;
		floor_y += step_y;

		ft_pixel_put(&game->mlx->img, x, y,
			*(unsigned int *)(game->mlx->textures[0].addr
				+ game->mlx->textures[0].line_len * tex_y + tex_x * 4));
	}

}