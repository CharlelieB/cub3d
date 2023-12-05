/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:45:19 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 14:43:47 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

static const char	*g_textures[] = {
	"NO",
	"SO",
	"WE",
	"EA"
};

bool	rgb_tokens(char *str, char *rgb[])
{
	int	count;

	count = 0;
	rgb[count] = str;
	while (*str)
	{
		if (*str == ',')
		{
			*(str++) = 0;
			++count;
			if (count > 2)
				return (false);
			rgb[count] = str;
		}
		else if (!ft_isdigit(*str))
			if (count != 2 || !is_space(*str))
				return (false);
		++str;
	}
	return (true);
}

int	parse_rgb(char *str)
{
	char	*rgb_ptr[3];
	int		rgb[3];
	int		i;

	i = 0;
	if (!rgb_tokens(str, rgb_ptr))
		return (-1);
	while (i < 3)
	{
		rgb[i] = ft_atoi_overflow(rgb_ptr[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
		++i;
	}
	return (rgb_to_hexa(rgb[0], rgb[1], rgb[2]));
}

bool	map_compare_surfaces(char *str, t_game *game)
{
	int	i;

	i = FLOOR;
	if (*str == 'C' || *str == 'F')
	{
		if (*str == 'C')
			i = SKY;
		++str;
		if (!is_space(*str))
			return (write(2, "Error\nSurface : wrong format\n", 29), false);
		while (is_space(*str))
				++str;
		game->surfaces_color[i] = parse_rgb(str);
		if (game->surfaces_color[i] == -1)
			return (write(2, "Error\nSurface : not RGB\n", 24), false);
		return (true);
	}
	return (write(2, "Error\nTexture : wrong format\n", 29), false);
}

bool	map_compare_direction(char *str, t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!ft_strncmp(str, g_textures[i], 2))
		{
			str += 2;
			if (!is_space(*str))
				return (write(2, "Error\nTexture : wrong format\n", 29), false);
			while (is_space(*str))
				++str;
			game->tex_path[i] = str;
			while (*str && !is_space(*str))
				++str;
			if (*str)
				*(str++) = 0;
			while (is_space(*str) && *str)
				++str;
			if (*str != 0)
				return (write(2, "Error\nTexture : wrong format\n", 29), false);
			return (true);
		}
	}
	return (map_compare_surfaces(str, game));
}

bool	map_check_assets(t_parsing *parsing, t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		while (is_space(*(parsing->assets[i])))
			++(*(parsing->map[i]));
		if (!map_compare_direction(parsing->assets[i], game))
			return (false);
		++i;
	}
	return (true);
}
