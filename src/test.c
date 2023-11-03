#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

#define PLAYER_DIR NORTH

int map[MAP_W * MAP_H] = {
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

bool	render(t_game *game)
{
	if (game->mlx->win_ptr == NULL)
		return (false);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, game->mlx->img.mlx_img, 0, 0);
	//mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, game->mlx->textures[0].mlx_img, 0, 0);
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

void draw(t_game *game)
{
	for (int i = 0; i < SCREEN_H_HALF; ++i)
	{
		for (int j = 0; j < SCREEN_W; ++j)
			ft_pixel_put(&game->mlx->img, j, i, 0x6ac7f9);
	}
	for (int i = SCREEN_H_HALF; i < SCREEN_H; ++i)
	{
		for (int j = 0; j < SCREEN_W; ++j)
			ft_pixel_put(&game->mlx->img, j, i, 0xffeb7b);
	}
	for (int i = 0; i < SCREEN_W; i++)
		raycasting(game, i);
	for (int i = 0; i < MAP_W; i++)
	{
		// for (int k = 0; k < MAP_W * 2; k++)
		// {
		// 	ft_pixel_put(&game->mlx->img, i * 2, k, 0xD5D5D5);
		// }
		for (int j = 0; j < MAP_H; j++)
		{
			// for (int k = 0; k < MAP_W * 2; k++)
			// {
			// 	ft_pixel_put(&game->mlx->img, k, j * 16, 0xD5D5D5);
			// }
			if (map[i + (MAP_W * j)] == 1)
			{
				draw_square(&game->mlx->img, i * 4, j * 4, 0x5FF236, 4);
			}
		}
	}
	draw_square(&game->mlx->img, (int)(game->ppos.x * 4), (int)(game->ppos.y * 4), 0x36A4F2, 4);
}

int	handle_no_event(void *game)
{
	if (game || !game)
		return (0);
	return (0);
}

void	move_player(int key, t_game *game)
{
	// float	x, y;
	float	speed;

	speed = 0.2;
	if (key == W)
	{
		if(map[(int)(game->ppos.x + game->pdir.x * speed) + (MAP_W * (int)game->ppos.y)] != 1) 
			game->ppos.x += game->pdir.x * speed;
		if(map[(int)game->ppos.x + (MAP_W * (int)(game->ppos.y + game->pdir.y * speed))] != 1) 
			game->ppos.y += game->pdir.y * speed;
		// x = game->ppos.x + (speed * game->pdir.x);
		// if (map[(int)x + (MAP_W * (int)game->pdir.y)] != 1)
		// 	game->ppos.x = x;
		// y = game->ppos.y + (speed * game->pdir.y);
		// if (map[(int)game->pdir.x + (MAP_W * (int)y)] != 1)
		// 	game->ppos.y = y;
	}
	else if (key == S)
	{  
		if(map[(int)(game->ppos.x - game->pdir.x * speed) + (MAP_W * (int)game->ppos.y)] != 1) 
			game->ppos.x -= game->pdir.x * speed;
		if(map[(int)game->ppos.x + (MAP_W * (int)(game->ppos.y - game->pdir.y * speed))] != 1) 
			game->ppos.y -= game->pdir.y * speed;  
		// x = game->ppos.x - (speed * game->pdir.x);
		// y = game->ppos.y - (speed * game->pdir.y);
		// if (map[(int)x + (MAP_W * (int)game->pdir.y)] != 1)
		// 	game->ppos.x = x;
		// if (map[(int)game->pdir.x + (MAP_W * (int)y)] != 1)
		// 	game->ppos.y = y;
	}
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}

void	move_direction(int key, t_game *game)
{
	float	old_x;
	float	old_plane_x;
	float	rot;

	rot = M_PI/180 * 2;
	old_x = game->pdir.x;
	old_plane_x = game->plane.x;
	if (key == D)
	{
		game->pdir.x = old_x * cos(rot) - game->pdir.y * sin(rot);
		game->pdir.y = old_x * sin(rot) + game->pdir.y * cos(rot);
		game->plane.x = old_plane_x * cos(rot) - game->plane.y * sin(rot);
		game->plane.y = old_plane_x * sin(rot) + game->plane.y * cos(rot);
	}
	else if (key == A)
	{
		game->pdir.x = old_x * cos(-rot) - game->pdir.y * sin(-rot);
		game->pdir.y = old_x * sin(-rot) + game->pdir.y * cos(-rot);
		game->plane.x = old_plane_x * cos(-rot) - game->plane.y * sin(-rot);
		game->plane.y = old_plane_x * sin(-rot) + game->plane.y * cos(-rot);
	}
	// printf("Before %.10f %.10f\n", game->pdir.x, game->pdir.y);
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		mlx_loop_end(game->mlx->mlx_ptr);
	// if (keysym == XK_w || keysym == XK_s)
	// 	move_player(keysym, game);
	// if (keysym == XK_a || keysym == XK_d)
	// 	move_direction(keysym, game);
	if (game->keys[W])
		move_player(W, game);
	else if (game->keys[S])
		move_player(S, game);
	if (game->keys[A])
		move_direction(A, game);
	else if (game->keys[D])
		move_direction(D, game);
	return (0);
}

int	set_key_release(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->keys[W] = 0;
	if (keysym == XK_a)
		game->keys[A] = 0;
	if (keysym == XK_s)
		game->keys[S] = 0;
	if (keysym == XK_d)
		game->keys[D] = 0;
	return (0);
}

int	set_key_press(int keysym, t_game *game)
{
	if (keysym == XK_w)
	{
		game->keys[W] = 1;
		game->keys[S] = 0;
	}
	else if (keysym == XK_a)
	{
		game->keys[A] = 1;
		game->keys[D] = 0;
	}
	else if (keysym == XK_s)
	{
		game->keys[S] = 1;
		game->keys[W] = 0;
	}
	else if (keysym == XK_d)
	{
		game->keys[D] = 1;
		game->keys[A] = 0;
	}
	handle_keypress(keysym, game);
	return (0);
}

void	mlx_functions(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, KeyPress, KeyPressMask, &set_key_press, game);
	mlx_hook(game->mlx->win_ptr, KeyRelease, KeyReleaseMask, &set_key_release, game);
	mlx_loop(game->mlx->mlx_ptr);
}

void	init(t_game *game)
{
	game->pdir.x = 1;
	game->pdir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66; //change based on player direction
	game->ppos.x = 17;
	game->ppos.y = 17;
	game->keys[W] = 0;
	game->keys[A] = 0;
	game->keys[S] = 0;
	game->keys[D] = 0;
}

void	test_texture(t_mlx *mlx)
{
	char *color;

	mlx->textures[0].mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/redbrick.xpm",&mlx->textures[0].width, &mlx->textures[0].height);
	if (mlx->textures[0].mlx_img == 0)
		printf("error couldn't load texture\n");
	mlx->textures[0].addr = mlx_get_data_addr(mlx->textures[0].mlx_img, &mlx->textures[0].bpp, &mlx->textures[0].line_len, &mlx->textures[0].endian);

	int indice = 34 * 4 + mlx->textures[0].line_len * 34;

	color = malloc(4);

	int c = 0;

	char *ptr = mlx->textures[0].addr;
	for (int i = 0; i <= 4; ++i)
	{
		c = c | *(ptr + i);
		if (i != 3)
			c <<= 8;
	}
	// c >>= 8;
	printf("======== %d\n", c);

	ft_memcpy(color, mlx->textures[0].addr + indice, 4);

	printf("test %d\n", indice);
	//print colors (4 char)
	for(int i = 0; i < 4; i++)
		printf("color %d\n", *(color + i));
	
}

int	main(void)
{
	t_game game;
	t_mlx mlx;

	game.mlx = &mlx;
	if (!set_img(&mlx))
		return (1);
	//parser
	test_texture(&mlx);
	init(&game);
	//game_loop_start
	draw(&game);
	render(&game);
	mlx_functions(&game);
	free_memory(&mlx);
	return (0);
}
