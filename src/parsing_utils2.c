/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:23:20 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 16:23:53 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

bool	ft_realloc(t_parsing *parsing)
{
	char	**new_map;
	int		i;

	i = 0;
	parsing->alloc_size = ft_next_power(parsing->alloc_size);
	new_map = malloc(parsing->alloc_size);
	if (!new_map)
	{
		write(2, "Failed to realloc\n", 18);
		free_map(parsing->map, parsing->map_h);
		return (false);
	}
	while (i < parsing->map_h)
	{
		*(new_map + i) = *(parsing->map + i);
		++i;
	}
	free(parsing->map);
	parsing->map = new_map;
	return (true);
}

void	free_stack_array_ptr(char *array[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(array[i]);
}
