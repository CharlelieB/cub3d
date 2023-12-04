/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:37:45 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/04 17:07:03 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_functions(t_game *game)
{
	mlx_hook(game->mlx->win_ptr, KeyPress, KeyPressMask, &set_key_press, game);
	mlx_hook(game->mlx->win_ptr, KeyRelease, KeyReleaseMask, &set_key_release, game);
	mlx_loop(game->mlx->mlx_ptr);
}

bool	set_img(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (false);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "CUB3D");
	if (!mlx->win_ptr)
	{
		free(mlx->mlx_ptr);
		return (false);
	}
	mlx->img.mlx_img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.mlx_img, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	return (true);
}

void	free_memory(t_mlx *mlx)
{
	mlx_loop(mlx->mlx_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->win_ptr = NULL;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.mlx_img);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
}
