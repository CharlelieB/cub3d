/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:37:45 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 17:24:52 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx->mlx_ptr);
	return (0);
}

void	mlx_functions(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, KeyPress, KeyPressMask,
		&set_key_press, game);
	mlx_hook(game->mlx->win_ptr, KeyRelease, KeyReleaseMask,
		&set_key_release, game);
	mlx_hook(game->mlx->win_ptr, DestroyNotify, 0, &close_window, game);
	mlx_loop(game->mlx->mlx_ptr);
}

bool	set_img(t_mlx *mlx)
{
	mlx->win_ptr = 0;
	mlx->mlx_ptr = 0;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (false);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W,
			SCREEN_H, "CUB3D");
	if (!mlx->win_ptr)
	{
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = 0;
		return (false);
	}
	mlx->img.mlx_img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!mlx->img.mlx_img)
		return (false);
	mlx->img.addr = mlx_get_data_addr(mlx->img.mlx_img, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	return (true);
}

void	free_memory(t_mlx *mlx)
{
	int	i;

	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->img.mlx_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.mlx_img);
	i = 0;
	while (i < 4)
	{
		if (mlx->textures[i].mlx_img)
			mlx_destroy_image(mlx->mlx_ptr, mlx->textures[i].mlx_img);
		++i;
	}
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
}
