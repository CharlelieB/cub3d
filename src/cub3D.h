#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdbool.h>

#define SCREEN_W 640
#define SCREEN_H 400

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

bool	set_img(t_mlx *mlx);
void	free_memory(t_mlx *mlx);

#endif