#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

#define SCREEN_W 1280
#define SCREEN_H 800
#define SCREEN_H_HALF 200
#define TEX_W 64
#define TEX_H 64
// #define MAP_W 24
// #define MAP_H 24

typedef float t_f;

//extern int map[MAP_W * MAP_H];

enum	e_direction
{
	NO,
	SO,
	WE,
	EA
};

enum	e_surface
{
	FLOOR,
	CEILING
};

enum	e_keys
{
	W,
	A,
	S,
	D
};

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
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
	t_img	textures[4];
}		t_mlx;

typedef struct	s_game
{
	char			*map;
	unsigned int	map_h;
	unsigned int	map_w;
	struct s_mlx	*mlx;
	struct s_vector	ppos;
	struct s_vector	pdir;
	struct s_vector	plane;
	char			*tex_path[4];
	int				surfaces_color[2];
	char			keys[4];
	float			rot;
}				t_game;

typedef struct	s_parsing
{
	char			**map;
	char			*assets[6];
	int			alloc_size;
	char 			*line;
	unsigned int	lsize;
	int				map_h;
	unsigned int	map_max_w;
	bool			player_found;
}				t_parsing;

typedef struct s_data
{
	t_vector	ray;
	float		side_x;
	float		side_y;
	int			side;
	int			map_x;
	int			map_y;
	float 		delta_x;
	float		delta_y;
	int			step_x;
	int			step_y;
	float 		wall_dist;
	int 		wall_height;
	int 		screen_x;
}				t_data;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	x_inc;
	int	y_inc;
	int	e;
}				t_line;

bool	game_loop(t_game *game);
bool	set_img(t_mlx *mlx);
void	free_memory(t_mlx *mlx);
void	draw_line(t_vector_int start, t_vector_int end, t_img *img);
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	raycasting(t_game *game, int x);
float	ft_fabs(float nb);

#endif
