#include "cub3D.h"

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
