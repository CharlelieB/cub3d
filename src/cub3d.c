#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

enum e_direction
{
		NORTH = 90,
		SOUTH = 270,
		EAST = 0,
		WEST = 180
};

typedef struct s_vector
{
	float x;
	float y;
}				t_vector;

typedef struct s_data
{
	int			screen_dist;
	t_vector	p_pos;
	t_vector	dir;
	t_vector	camera;
	t_vector	plane;	
}			t_data;

#define FOV 60
#define H_FOV 30
#define PLAYER_POS_X 2 
#define PLAYER_POS_Y 3
#define PLAYER_DIR NORTH
#define PLANE_HW 160
#define RAY_INCREMENT 60/320
#define MAP_X 24
#define MAP_Y 24

const int map[] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

/*
void calculate_distance(t_data *data)
{
	int	line_h;
	int	draw_start;
	int	draw_end;

	if (side == 0)
		wall_dist = side_dist_x - delta_dist_x;
	else
		wall_dist = side_dist_y - delta_dist_y;
		
	line_h = (int)(h/wall_dist);
	draw_start = -line_h / 2 + h / 2;

}

void	dda(t_data *data)
{
	int	map_x;
	int	map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	wall_dist;
	int		wall;

	map_y = (int)P_POS_X;
	map_x = (int)P_POS_X;

	//len of ray from one x or y side to next x/y
	delta_dist_x = (ray_dir_x == 0) ? FLT_MAX : abs(1/ray_dir_x); //avoir division by zero
	delta_dist_y = (ray_dir_y == 0) ? FLT_MAX : abs(1/ray_dir_y); //avoir division by zero

	//what direction to step in x or y direction (+1 or -1)
	int step_x;
	int step_y;

     //calculate step and initial sideDist
     if (rayDirX < 0)
     {
       stepX = -1;
       sideDistX = (posX - mapX) * deltaDistX;
     }
     else
     {
      stepX = 1;
       sideDistX = (mapX + 1.0 - posX) * deltaDistX;
     }
     if (rayDirY < 0)
     {
       stepY = -1;
       sideDistY = (posY - mapY) * deltaDistY;
     }
     else
     {
       stepY = 1;
       sideDistY = (mapY + 1.0 - posY) * deltaDistY;
     }

	wall = 0; //was there a wall hit?
	int side; //was a NS / EW wall

	while (wall == 0)
	{
  	 //jump to next map square, either in x-direction, or in y-direction
		if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (map[mapX][mapY] > 0)
			wall = 1;
	}
	calculate_distance(data);
}

void raycast(t_data *data)
{
	int	i;
	float	ray_dir_x;
	float	ray_dir_y;

	ray_angle = PLAYER_DIR - H_FOV; 
	i = 0;
	//for every vertical slice of the screen
	while (i < SCREEN_W)
	{
		data->camera->x = 2 * i / (float)SCREEN_W - 1;
		ray_dir_x = data->dir->x + data->plane->x * data->camera->x;
		ray_dir_y = data->dir->y + data->plane->y * data->camera->x;
		//DDA
		dda(data);
		i++;
	}
}
*/

bool	render(t_mlx *mlx)
{
		if (mlx->win_ptr == NULL)
			return (false);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.mlx_img, 0, 0);
		return (true);
}
int	main(void)
{
	//t_data data;
	t_mlx mlx;

	if (!set_img(&mlx))
		return (1);
	//data.screen_dist = PLANE_HW / tan(H_FOV * M_PI/180);
	//parser
	//init();
	//game_loop_start
	//raycast();
	render(&mlx);
	mlx_loop(mlx.mlx_ptr);
	free_memory(&mlx);
	return (0);
}
