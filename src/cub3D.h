#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdbool.h>
#include "libft.h"

#define SCREEN_W 640
#define SCREEN_H 400
#define SCREEN_H_HALF 200

enum	e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	bool	is_clean;
}				t_img;

typedef struct	s_vector
{
	float	x;
	float	y;
}		t_vector;

typedef struct	s_vector_int
{
	int	x;
	int	y;
}		t_vector_int;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}		t_mlx;

typedef struct	s_data
{
	struct s_mlx	*mlx;
	struct s_vector	ppos;	
	struct s_vector	pdir;
	struct s_vector	plane;
}		t_data;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	x_inc;
	int	y_inc;
	int	e;
}				t_line;

bool	set_img(t_mlx *mlx);
void	free_memory(t_mlx *mlx);
void	draw_line(t_vector_int start, t_vector_int end, t_img *img);
void	ft_pixel_put(t_img *img, int x, int y, int color);

#endif
