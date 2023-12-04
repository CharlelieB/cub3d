/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:56:37 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/04 14:56:38 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	rgb_to_hexa(unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	if (r < 0 || g < 0 || b < 0)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

bool	is_empty(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (false);
		++str;
	}
	return (true);
}

int	ft_atoi_overflow(const char *nptr)
{
	int	nb;
	int	prev;

	nb = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (ft_isdigit(*nptr))
	{
		prev = nb;
		nb = 10 * nb + (*nptr - 48);
		if (nb < prev)
			return (-1);
		nptr++;
	}
	return (nb);
}

void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(*(map + i));
		++i;
	}
	free(map);
}
