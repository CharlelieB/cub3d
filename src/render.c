/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:27:45 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/06 16:19:55 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

/* 
y = i / W
x = i % W

. If you make W a power of 2 (W=2^m), you can use the hack

y = i >> m;
x = (i & (W-1))

*/
void	ft_clear_image(t_img *img)
{
	unsigned long int	i;
	unsigned int		w_minus_one;

	w_minus_one = SCREEN_W - 1;
	i = 0;
	while (i < SCREEN_S)
	{
		ft_pixel_put(img, (i & w_minus_one), i >> 32, 0x0);
		++i;
	}
}

bool	render(t_game *game)
{
	if (game->mlx->win_ptr == NULL)
		return (false);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr,
		game->mlx->img.mlx_img, 0, 0);
	return (true);
}
