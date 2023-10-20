#include "cub3D.h"

void	line2(t_vector_int *start, t_vector_int *end, t_img *img)
{
	t_line	line_data;

	line_data.dx = end->x - start->x;
	line_data.dy = end->y - start->y;
	line_data.x_inc = 1;
	if (line_data.dx < 0)
	{
		line_data.x_inc = -1;
		line_data.dx = -line_data.dx;
	}
	line_data.e = 2 * line_data.dx - line_data.dy;
	while (start->y <= end->y)
	{
		if (start->x >= 0 && start->y >= 0
			&& start->x < SCREEN_W && start->y < SCREEN_H)
			ft_pixel_put(img, start->x, start->y, 0xF23636);
		(start->y)++;
		if (line_data.e < 0)
			line_data.e += 2 * line_data.dx;
		else
		{
			line_data.e += 2 * (line_data.dx - line_data.dy);
			start->x += line_data.x_inc;
		}
	}
}

void	line1(t_vector_int *start, t_vector_int *end, t_img *img)
{
	t_line	line_data;

	line_data.dx = end->x - start->x;
	line_data.dy = end->y - start->y;
	line_data.y_inc = 1;
	if (line_data.dy < 0)
	{
		line_data.y_inc = -1;
		line_data.dy = -line_data.dy;
	}
	line_data.e = 2 * line_data.dy - line_data.dx;
	while (start->x <= end->x)
	{
		if (start->x >= 0 && start->y >= 0
			&& start->x < SCREEN_W && start->y < SCREEN_H)
			ft_pixel_put(img, start->x, start->y, 0xF23636);
		(start->x)++;
		if (line_data.e < 0)
			line_data.e += 2 * line_data.dy;
		else
		{
			line_data.e += 2 * (line_data.dy - line_data.dx);
			start->y += line_data.y_inc;
		}	
	}
}

void	draw_line(t_vector_int start, t_vector_int end, t_img *img)
{
	if (ft_abs(end.x - start.x) >= ft_abs(end.y - start.y))
	{
		if (start.x > end.x)
		{
			ft_swap(&(start.x), &(end.x));
			ft_swap(&(start.y), &(end.y));
		}
		line1(&start, &end, img);
	}
	else
	{
		if (start.y > end.y)
		{
			ft_swap(&(start.x), &(end.x));
			ft_swap(&(start.y), &(end.y));
		}
		line2(&start, &end, img);
	}
}