#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

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
	int	i;
	int	j;
	int	color;

	i = 0;
	for (; i < SCREEN_H_HALF; ++i)
	{
		for (j = 0; j < SCREEN_W; ++j)
			ft_pixel_put(&game->mlx->img, j, i, game->surfaces_color[SKY]);
	}
	for (i = SCREEN_H_HALF; i < SCREEN_H; ++i)
	{
		for (j = 0; j < SCREEN_W; ++j)
			ft_pixel_put(&game->mlx->img, j, i, game->surfaces_color[FLOOR]);
	}
	for (i = 0; i < SCREEN_W; i++)
		raycasting(game, i);
	for (i = 0; i < (int)game->map_w; i++)
	{
		for (j = 0; j < (int)game->map_h; j++)
		{
			if (game->map[i + (game->map_w * j)] == '1')
				color = 0xFFFFFF;
			else
				color = 0;
			draw_square(&game->mlx->img, i * 4, j * 4, color, 4);
		}
	}
	draw_square(&game->mlx->img, (int)(game->ppos.x * 4), (int)(game->ppos.y * 4), 0xff3333, 4);
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

	speed = 0.4;
	if (key == W)
	{
		if(game->map[(int)(game->ppos.x + game->pdir.x * speed) + (game->map_w * (int)game->ppos.y)] != '1') 
			game->ppos.x += game->pdir.x * speed;
		if(game->map[(int)game->ppos.x + (game->map_w * (int)(game->ppos.y + game->pdir.y * speed))] != '1') 
			game->ppos.y += game->pdir.y * speed;
	}
	else if (key == S)
	{  
		if(game->map[(int)(game->ppos.x - game->pdir.x * speed) + (game->map_w * (int)game->ppos.y)] != '1') 
			game->ppos.x -= game->pdir.x * speed;
		if(game->map[(int)game->ppos.x + (game->map_w * (int)(game->ppos.y - game->pdir.y * speed))] != '1') 
			game->ppos.y -= game->pdir.y * speed;
	}
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}

void	move_direction(int key, t_game *game)
{
	float	old_x;
	float	old_plane_x;

	old_x = game->pdir.x;
	old_plane_x = game->plane.x;
	if (key == D)
	{
		game->pdir.x = old_x * cos(game->rot) - game->pdir.y * sin(game->rot);
		game->pdir.y = old_x * sin(game->rot) + game->pdir.y * cos(game->rot);
		game->plane.x = old_plane_x * cos(game->rot) - game->plane.y * sin(game->rot);
		game->plane.y = old_plane_x * sin(game->rot) + game->plane.y * cos(game->rot);
	}
	else if (key == A)
	{
		game->pdir.x = old_x * cos(-game->rot) - game->pdir.y * sin(-game->rot);
		game->pdir.y = old_x * sin(-game->rot) + game->pdir.y * cos(-game->rot);
		game->plane.x = old_plane_x * cos(-game->rot) - game->plane.y * sin(-game->rot);
		game->plane.y = old_plane_x * sin(-game->rot) + game->plane.y * cos(-game->rot);
	}
	ft_clear_image(&game->mlx->img);
	draw(game);
	render(game);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		mlx_loop_end(game->mlx->mlx_ptr);
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
	if (game->pdir.y == -1 || game->pdir.x == 1)
		game->rot = (M_PI/180 * 4);
	else
		game->rot = -(M_PI/180 * 4);
	game->keys[W] = 0;
	game->keys[A] = 0;
	game->keys[S] = 0;
	game->keys[D] = 0;
}

bool	load_textures(t_mlx *mlx, t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx->textures[i].mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			game->tex_path[i], &mlx->textures[i].width, &mlx->textures[i].height);
		if (mlx->textures[i].mlx_img == 0)
		{
			write(2, "Error\nCouldn't load texture\n", 28);
			return (false);
		}
		mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].mlx_img,
			&mlx->textures[i].bpp, &mlx->textures[i].line_len, &mlx->textures[i].endian);
		if (mlx->textures[i].addr == 0)
		{
			write(2, "Error\nCouldn't get img addr\n", 28);
			return (false);
			//TODO: Destroy image if error !!
		}
		++i;
	}
	return (true);
}

bool	game_loop(t_game *game)
{
	t_mlx mlx;

	game->mlx = &mlx;
	if (!set_img(&mlx))
		return (false);
	//parser
	if (!load_textures(&mlx, game))
		return (false);
	init(game);
	//game_loop_start
	draw(game);
	render(game);
	mlx_functions(game);
	free_memory(&mlx);
	return (true);
}
