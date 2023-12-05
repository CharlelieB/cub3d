/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:21:34 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 16:27:38 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

void	delta_set(t_data *data)
{
	if (data->ray.x == 0)
		data->delta_x = 1.0e30f;
	else
		data->delta_x = fabs(1 / data->ray.x);
	if (data->ray.y == 0)
		data->delta_y = 1.0e30f;
	else
		data->delta_y = fabs(1 / data->ray.y);
}

void	dda_init(t_game *game, t_data *data)
{
	delta_set(data);
	if (data->ray.x < 0)
	{
		data->step_x = -1;
		data->side_x = (game->ppos.x - (t_f)data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->side_x = ((t_f)data->map_x + 1.0 - game->ppos.x) * data->delta_x;
	}
	if (data->ray.y < 0)
	{
		data->step_y = -1;
		data->side_y = (game->ppos.y - (t_f)data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->side_y = ((t_f)data->map_y + 1.0 - game->ppos.y) * data->delta_y;
	}
}
