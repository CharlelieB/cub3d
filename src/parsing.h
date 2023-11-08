#ifndef PARSING_H
# define PARSING_H

//UTILS

# define ERR_FILE_NOT_CUB "Not a .cub file"

int		ft_atoi_overflow(const char *nptr);
bool	is_empty(char *str);
int		is_space(char c);
int		rgb_to_hexa(unsigned char r, unsigned char g, unsigned char b);
void	free_map(char **map, int size);

bool	map_check_assets(t_parsing *parsing, t_game *game);
bool	flood_fill(t_game *game, int x, int y);

#endif