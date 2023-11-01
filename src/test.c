#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

#define PLAYER_DIR NORTH
#define MAP_W 24
#define MAP_H 24
#define TILE_SIZE 16

int map[] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

float	ft_fabs(float nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

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

void	draw_walls(t_data *data, int side, float side_dist_x,
	float side_dist_y, float deltaDistX, float deltaDistY, int x)
{
	float	wall_dist;
	int 	line_height;
	int 	draw_start;
	int 	draw_end;

	if(side == 0)
		wall_dist = ft_fabs(side_dist_x - deltaDistX);
    else
		wall_dist = ft_fabs(side_dist_y - deltaDistY);
	if (wall_dist)
		line_height = ft_abs((int)(SCREEN_H / wall_dist));
	else
		line_height = INFINITY;
	// if (side == 0)
	// 	printf("test side = 0:  wall %f %f %f\n", wall_dist, side_dist_x, deltaDistX);
	// else
	// 	printf("test side = 1: wall %f %f %f\n", wall_dist, side_dist_y, deltaDistY);
    draw_start = -line_height / 2 + SCREEN_H_HALF;
    if(draw_start < 0)
		draw_start = 0;
    draw_end = line_height / 2 + SCREEN_H_HALF;
    if(draw_end >= SCREEN_H)
		draw_end = SCREEN_H - 1;
	int color = 0x232323;
	if (side == 1)
		color = 0x5f5f5f;
	int count = draw_end - draw_start;
	// printf("%d %d\n", draw_start, draw_end);
	for (int i = 0; i < count; i++)
	{
		ft_pixel_put(&data->mlx->img, x, draw_start, color);
		++draw_start;
	}
}

void	draw_direction(t_data *data, int x)
{
	float		side_dist_x;
	float		side_dist_y;
	t_vector	ray;
	int		stepX, stepY;
	int		hit;
	int map_x, map_y;
	int	side;
	float camera_x = 2 * x / (float)SCREEN_W - 1;

	ray.x = data->pdir.x + data->plane.x * camera_x;
	ray.y = data->pdir.y + data->plane.y * camera_x;
	map_x = (int)data->ppos.x;
	map_y = (int)data->ppos.y;
	float deltaDistX;
	float deltaDistY;

	if (ray.x == 0)
		deltaDistX = 1.0e30f;
	else
		deltaDistX = ft_fabs(1 / ray.x);
	if (ray.y == 0)
		deltaDistY = 1.0e30f;
	else
		deltaDistY = ft_fabs(1 / ray.y);
	hit = 0;

	if (ray.x < 0)
	{
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
	//printf("ray.x : %f ray.y : %f | SideDistX %f, SideDistY %f DeltaX %f DeltaY %f\n", ray.x, ray.y, side_dist_x, side_dist_y, deltaDistX, deltaDistY);
	// printf("test -- %f %f\n", ((float) map_x + 1.0 - data->ppos.x), deltaDistX);
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += deltaDistX;
			map_x += stepX;
			side = 0;
		}
		else
		{
			side_dist_y += deltaDistY;
			map_y += stepY;
			side = 1;
		}
		if (map[map_x + (map_y * MAP_W)] == 1)
			hit = 1;
	}
	/* 
	To draw ray in 2d (minimap)
	t_vector_int end;
	t_vector_int start;

	start.x = (int)(data->ppos.x * 16) + 4;
	start.y = (int)(data->ppos.y * 16) + 4;	
	end.x = map_x * 16;
	end.y = map_y * 16;
	printf("Start : X = %d Y = %d | End : X = %d Y = %d\n", (int)data->ppos.x, (int)data->ppos.y, 
	map_x, map_y);
	draw_line(start, end, &data->mlx->img);
	*/
	draw_walls(data, side, side_dist_x, side_dist_y, deltaDistX, deltaDistY, x);
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
	for (int i = 0; i < SCREEN_H_HALF; ++i)
	{
		for (int j = 0; j < SCREEN_W; ++j)
			ft_pixel_put(&data->mlx->img, j, i, 0x6ac7f9);
	}
	for (int i = SCREEN_H_HALF; i < SCREEN_H; ++i)
	{
		for (int j = 0; j < SCREEN_W; ++j)
			ft_pixel_put(&data->mlx->img, j, i, 0xffeb7b);
	}
	for (int i = 0; i < SCREEN_W; i++)
		draw_direction(data, i);
	for (int i = 0; i < MAP_W; i++)
	{
		// for (int k = 0; k < MAP_W * 2; k++)
		// {
		// 	ft_pixel_put(&data->mlx->img, i * 2, k, 0xD5D5D5);
		// }
		for (int j = 0; j < MAP_H; j++)
		{
			// for (int k = 0; k < MAP_W * 2; k++)
			// {
			// 	ft_pixel_put(&data->mlx->img, k, j * 16, 0xD5D5D5);
			// }
			if (map[i + (MAP_W * j)] == 1)
			{
				draw_square(&data->mlx->img, i * 4, j * 4, 0x5FF236, 4);
			}
		}
	}
	// t_vector_int start;
	// t_vector_int end;
	// start.x = (int)(data->ppos.x * 4);
	// start.y = (int)(data->ppos.y * 4);
	// end.x = (int)ft_abs_float(1 / data->pdir.x);
	// end.y = (int)ft_abs_float(1 / data->pdir.y);
	// draw_line(start, end, &data->mlx->img);
	draw_square(&data->mlx->img, (int)(data->ppos.x * 4), (int)(data->ppos.y * 4), 0x36A4F2, 4);
}

int	handle_no_event(void *data)
{
	if (data || !data)
		return (0);
	return (0);
}

void	move_player(int key, t_data *data)
{
	// float	x, y;
	float	speed;

	speed = 0.2;
	if (key == W)
	{
		if(map[(int)(data->ppos.x + data->pdir.x * speed) + (MAP_W * (int)data->ppos.y)] != 1) 
			data->ppos.x += data->pdir.x * speed;
		if(map[(int)data->ppos.x + (MAP_W * (int)(data->ppos.y + data->pdir.y * speed))] != 1) 
			data->ppos.y += data->pdir.y * speed;
		// x = data->ppos.x + (speed * data->pdir.x);
		// if (map[(int)x + (MAP_W * (int)data->pdir.y)] != 1)
		// 	data->ppos.x = x;
		// y = data->ppos.y + (speed * data->pdir.y);
		// if (map[(int)data->pdir.x + (MAP_W * (int)y)] != 1)
		// 	data->ppos.y = y;
	}
	else if (key == S)
	{  
		if(map[(int)(data->ppos.x - data->pdir.x * speed) + (MAP_W * (int)data->ppos.y)] != 1) 
			data->ppos.x -= data->pdir.x * speed;
		if(map[(int)data->ppos.x + (MAP_W * (int)(data->ppos.y - data->pdir.y * speed))] != 1) 
			data->ppos.y -= data->pdir.y * speed;  
		// x = data->ppos.x - (speed * data->pdir.x);
		// y = data->ppos.y - (speed * data->pdir.y);
		// if (map[(int)x + (MAP_W * (int)data->pdir.y)] != 1)
		// 	data->ppos.x = x;
		// if (map[(int)data->pdir.x + (MAP_W * (int)y)] != 1)
		// 	data->ppos.y = y;
	}
	ft_clear_image(&data->mlx->img);
	draw(data);
	render(data);
}

void	move_direction(int key, t_data *data)
{
	float	old_x;
	float	old_plane_x;
	float	rot;

	rot = M_PI/180 * 2;
	old_x = data->pdir.x;
	old_plane_x = data->plane.x;
	if (key == D)
	{
		data->pdir.x = old_x * cos(rot) - data->pdir.y * sin(rot);
		data->pdir.y = old_x * sin(rot) + data->pdir.y * cos(rot);
		data->plane.x = old_plane_x * cos(rot) - data->plane.y * sin(rot);
		data->plane.y = old_plane_x * sin(rot) + data->plane.y * cos(rot);
	}
	else if (key == A)
	{
		data->pdir.x = old_x * cos(-rot) - data->pdir.y * sin(-rot);
		data->pdir.y = old_x * sin(-rot) + data->pdir.y * cos(-rot);
		data->plane.x = old_plane_x * cos(-rot) - data->plane.y * sin(-rot);
		data->plane.y = old_plane_x * sin(-rot) + data->plane.y * cos(-rot);
	}
	// printf("Before %.10f %.10f\n", data->pdir.x, data->pdir.y);
	ft_clear_image(&data->mlx->img);
	draw(data);
	render(data);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx->mlx_ptr);
	// if (keysym == XK_w || keysym == XK_s)
	// 	move_player(keysym, data);
	// if (keysym == XK_a || keysym == XK_d)
	// 	move_direction(keysym, data);
	if (data->keys[W])
		move_player(W, data);
	else if (data->keys[S])
		move_player(S, data);
	if (data->keys[A])
		move_direction(A, data);
	else if (data->keys[D])
		move_direction(D, data);
	return (0);
}

int	set_key_release(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->keys[W] = 0;
	if (keysym == XK_a)
		data->keys[A] = 0;
	if (keysym == XK_s)
		data->keys[S] = 0;
	if (keysym == XK_d)
		data->keys[D] = 0;
	return (0);
}

int	set_key_press(int keysym, t_data *data)
{
	if (keysym == XK_w)
	{
		data->keys[W] = 1;
		data->keys[S] = 0;
	}
	else if (keysym == XK_a)
	{
		data->keys[A] = 1;
		data->keys[D] = 0;
	}
	else if (keysym == XK_s)
	{
		data->keys[S] = 1;
		data->keys[W] = 0;
	}
	else if (keysym == XK_d)
	{
		data->keys[D] = 1;
		data->keys[A] = 0;
	}
	handle_keypress(keysym, data);
	return (0);
}

void	mlx_functions(t_data *data)
{
	mlx_hook(data->mlx->win_ptr, KeyPress, KeyPressMask, &set_key_press, data);
	mlx_hook(data->mlx->win_ptr, KeyRelease, KeyReleaseMask, &set_key_release, data);
	mlx_loop(data->mlx->mlx_ptr);
}

void	init(t_data *data)
{
	data->pdir.x = 1;
	data->pdir.y = 0;
	data->plane.x = 0;
	data->plane.y = 0.66; //change based on player direction
	data->ppos.x = 17;
	data->ppos.y = 17;
	data->keys[W] = 0;
	data->keys[A] = 0;
	data->keys[S] = 0;
	data->keys[D] = 0;
}

int	main(void)
{
	t_data data;
	t_mlx mlx;

	data.mlx = &mlx;
	if (!set_img(&mlx))
		return (1);
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
