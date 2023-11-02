#include "cub3D.h"

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
	// mlx->img.mlx_img = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	int size;
	size = 64;
	mlx->img.mlx_img = mlx_xpm_file_to_image(mlx, "./textures/brickwall.xpm", &size, &size);
	if (mlx->img.mlx_img == NULL)
		printf("couldn't loadeeeee texture\n");
	mlx->img.addr = mlx_get_data_addr(mlx->img.mlx_img, &mlx->img.bpp, &mlx->img.line_len, &mlx->img.endian);
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
