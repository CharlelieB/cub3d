#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

#define FOV 60
#define H_FOV 30
#define PLAYER_POS_X 2 
#define PLAYER_POS_Y 3
#define PLAYER_DIR NORTH
#define PLANE_HW 160
#define RAY_INCREMENT 60/320
#define MAP_W 24
#define MAP_H 24

int map[] = {
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
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	ft_clear_image(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_W)
	{
		j = 0;
		while (j < SCREEN_H)
		{
			ft_pixel_put(img, i, j, 0x0);
			j++;
		}
		i++;
	}
}

void	draw_direction(t_data *data)
{
	float		side_dist_x;
	float		side_dist_y;
	t_vector	ray;
	int		stepX, stepY;
	int		hit;
	int map_x, map_y;
	//int	side;
	ray.x = data->pdir.x;
	ray.y = data->pdir.y;
	map_x = (int)data->ppos.x;
	map_y = (int)data->ppos.y;
	float deltaDistX = (ray.x == 0) ? 1e30 : ft_abs(1 / ray.x);
	float deltaDistY = (ray.y == 0) ? 1e30 : ft_abs(1 / ray.y);
	hit = 0;
	if (ray.x < 0)
	{
	printf("test----- %.10f\n", ray.x);
		stepX = -1;
		side_dist_x = (data->ppos.x - (float) map_x) * deltaDistX;
	}
	else
	{
		stepX = 1;
		side_dist_x = ((float) map_x + 1.0 - data->ppos.x) * deltaDistX;
	}
	if (ray.y < 0)
	{
		stepY = -1;
		side_dist_y = (data->ppos.y - (float) map_y) * deltaDistY;
	}
	else
	{
		stepY = 1;
		side_dist_y = ((float) map_y + 1.0 - data->ppos.y) * deltaDistY;
	}
	while (hit == 0)
	{
		//ft_pixel_put(&data->mlx->img, 16 + map_x, 16 + map_y, 0xF23636);
		if (side_dist_x < side_dist_y)
		{
			printf("test debug %f\n", side_dist_x);
			side_dist_x += deltaDistX;
			map_x += stepX;
			//side = 0;
		}
		else
		{
			side_dist_y += deltaDistY;
			map_y += stepY;
			//side = 1;
		}
		if (map[map_x + (map_y * MAP_W)] == 1)
			hit = 1;
	}
	t_vector_int end;
	t_vector_int start;

	start.x = (int)(data->ppos.x * 16);
	start.y = (int)(data->ppos.y * 16);
	end.x = map_x * 16;
	end.y = map_y * 16;
	draw_line(start, end, &data->mlx->img);
}

bool	render(t_data *data)
{
		if (data->mlx->win_ptr == NULL)
			return (false);
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->mlx->img.mlx_img, 0, 0);
		return (true);
}

void draw_square(t_img *img, int x, int y, int color, int size)
{
	int draw_x, draw_y;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			draw_x = i + x;
			draw_y = j + y;
			if (draw_x >= 0 && draw_y >= 0 && draw_x < SCREEN_W && draw_y < SCREEN_H)
			ft_pixel_put(img, draw_x, draw_y, color);
		}
	}

}

void draw(t_data *data)
{

	//player_x = SCREEN_W/2;
	//player_y = SCREEN_H/2;
	//draw walls
	for (int i = 0; i < MAP_W; i++)
	{
		for (int k = 0; k < MAP_W * 16; k++)
		{
			ft_pixel_put(&data->mlx->img, i * 16, k, 0xD5D5D5);
		}
		for (int j = 0; j < MAP_H; j++)
		{
			for (int k = 0; k < MAP_W * 16; k++)
			{
				ft_pixel_put(&data->mlx->img, k, j * 16, 0xD5D5D5);
			}
			if (map[i + (MAP_W * j)] == 1)
			{
				draw_square(&data->mlx->img, i * 16, j * 16, 0x5FF236, 16);
			}
		}
	}
	draw_direction(data);
	//draw player
	draw_square(&data->mlx->img, (int)(data->ppos.x * 16), (int)(data->ppos.y * 16), 0x36A4F2, 8);
}

int	handle_no_event(void *data)
{
	if (data || !data)
		return (0);
	return (0);
}

void	move_player(int key, t_data *data)
{
	float	x, y;

	if (key == XK_a || key == XK_d)
	{
		if (key == XK_a)
			x = data->ppos.x - 0.2;
		else
			x = data->ppos.x + 0.2;
		if (x < 0 || x >= MAP_W || map[(int)x + (MAP_W * (int)data->ppos.y)] == 1)
			return ;
		data->ppos.x = x;
	}
	else if (key == XK_w || key == XK_s)
	{
		if (key == XK_w)
			y = data->ppos.y - 0.2;
		else
			y = data->ppos.y + 0.2;
		if (y < 0 || y >= MAP_H || map[(int)data->ppos.x + (MAP_W * (int)y)] == 1)
			return ;
		data->ppos.y = y;
	}
	ft_clear_image(&data->mlx->img);
	draw(data);
	render(data);
}

void	move_direction(int key, t_data *data)
{
	float	old_x;
	float	rot;

	old_x = data->pdir.x;
	rot = M_PI/180 * 10;

	if (key == XK_Left)
	{
		data->pdir.x = old_x * cos(rot) - data->pdir.y * sin(rot);
		data->pdir.y = old_x * sin(rot) + data->pdir.y * cos(rot);
	}
	else if (key == XK_Right)
	{
		data->pdir.x = old_x * cos(-rot) - data->pdir.y * sin(-rot);
		data->pdir.y = old_x * sin(-rot) + data->pdir.y * cos(-rot);
	}
	printf("Before %.10f %.10f\n", data->pdir.x, data->pdir.y);
	ft_clear_image(&data->mlx->img);
	draw(data);
	render(data);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx->mlx_ptr);
	if (keysym == XK_a || keysym == XK_d || keysym == XK_w || keysym == XK_s)
		move_player(keysym, data);
	if (keysym == XK_Left || keysym == XK_Right)
		move_direction(keysym, data);
	return (0);
}

void	mlx_functions(t_data *data)
{
	mlx_hook(data->mlx->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx->mlx_ptr);
}

void	init(t_data *data)
{
	data->pdir.x = 0;
	data->pdir.y = 1;
}

int	main(void)
{
	t_data data;
	t_mlx mlx;

	data.mlx = &mlx;
	if (!set_img(&mlx))
		return (1);
	data.ppos.x = 12;
	data.ppos.y = 12;
	data.pdir.x = 0;
	data.pdir.y = 1;
	//data.plane.x = 0, data.plane.y = 0.60;
	//data.screen_dist = PLANE_HW / tan(H_FOV * M_PI/180);
	//parser
	init(&data);
	//game_loop_start
	//raycast();
	draw(&data);
	render(&data);
	mlx_functions(&data);
	free_memory(&mlx);
	return (0);
}
