/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:06 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/06 13:03:51 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

void	draw(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_H_HALF)
	{
		j = -1;
		while (++j < SCREEN_W)
			ft_pixel_put(&game->mlx->img, j, i, game->surfaces_color[SKY]);
		++i;
	}
	i = SCREEN_H_HALF;
	while (i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
			ft_pixel_put(&game->mlx->img, j, i, game->surfaces_color[FLOOR]);
		++i;
	}
	i = -1;
	while (++i < SCREEN_W)
		raycasting(game, i);
}

int	handle_no_event(void *game)
{
	if (game || !game)
		return (0);
	return (0);
}

void	init_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->pdir.y == -1 || game->pdir.x == 1)
		game->rot = (M_PI / 180 * 4);
	else
		game->rot = -(M_PI / 180 * 4);
	game->keys[W] = 0;
	game->keys[A] = 0;
	game->keys[S] = 0;
	game->keys[D] = 0;
	game->mlx->img.mlx_img = 0;
	while (i < 4)
	{
		game->mlx->textures[i].mlx_img = 0;
		++i;
	}
}

bool	load_textures(t_mlx *mlx, t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx->textures[i].mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr,
				game->tex_path[i], &mlx->textures[i].width,
				&mlx->textures[i].height);
		if (mlx->textures[i].mlx_img == 0)
		{
			write(2, "Error\nCouldn't load texture\n", 28);
			return (false);
		}
		mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].mlx_img,
				&mlx->textures[i].bpp, &mlx->textures[i].line_len,
				&mlx->textures[i].endian);
		if (mlx->textures[i].addr == 0)
		{
			write(2, "Error\nCouldn't get img addr\n", 28);
			return (false);
		}
		++i;
	}
	return (true);
}

void	game_loop(t_game *game)
{
	t_mlx	mlx;

	game->mlx = &mlx;
	init_game(game);
	if (set_img(&mlx) && load_textures(&mlx, game))
	{
		draw(game);
		render(game);
		mlx_functions(game);
	}
	free_memory(&mlx);
}
