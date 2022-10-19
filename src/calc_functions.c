/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:07:25 by eward             #+#    #+#             */
/*   Updated: 2022/10/19 18:07:27 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"
#include "cube3d.h"

void	init_calc(t_data *data, t_calc *calc, int x)
{
	calc->camera_x = 2 * x / (double) screenWidth - 1;
	calc->ray_dir_x = data->dir_x + data->plane_x * calc->camera_x;
	calc->ray_dir_y = data->dir_y + data->plane_y * calc->camera_x;
	calc->map_x = (int)data->pos_x ;
	calc->map_y = (int)data->pos_y;
	if (calc->ray_dir_x == 0)
		calc->delta_dist_x = 1e30;
	else
		calc->delta_dist_x = fabs(1 / calc->ray_dir_x);
	if (calc->ray_dir_y == 0)
		calc->delta_dist_y = 1e30;
	else
		calc->delta_dist_y = fabs(1 / calc->ray_dir_y);
	calc->hit = 0;
	calc_step_and_side_dist(data, calc);
}

void	calc_step_and_side_dist(t_data *data, t_calc *calc)
{
	if (calc->ray_dir_x < 0)
	{
		calc->step_x = -1;
		calc->side_dist_x = (data->pos_x - calc->map_x)
			* calc->delta_dist_x;
	}
	else
	{
		calc->step_x = 1;
		calc->side_dist_x = (calc->map_x + 1.0
				- data->pos_x) * calc->delta_dist_x;
	}
	if (calc->ray_dir_y < 0)
	{
		calc->step_y = -1;
		calc->side_dist_y = (data->pos_y - calc->map_y) * calc->delta_dist_y;
	}
	else
	{
		calc->step_y = 1;
		calc->side_dist_y = (calc->map_y + 1.0
				- data->pos_y) * calc->delta_dist_y;
	}
}

void	dda(char **world_map, t_calc *calc)
{
	while (calc->hit == 0)
	{
		if (calc->side_dist_x < calc->side_dist_y)
		{
			calc->side_dist_x += calc->delta_dist_x;
			calc->map_x += calc->step_x;
			calc->side = 0;
		}
		else
		{
			calc->side_dist_y += calc->delta_dist_y;
			calc->map_y += calc->step_y;
			calc->side = 1;
		}
		if (world_map[calc->map_x][calc->map_y] > 0)
			calc->hit = 1;
	}
}

void	calc_line_height(t_calc *calc)
{
	if (calc->side == 0)
		calc->perp_wall_dist = (calc->side_dist_x - calc->delta_dist_x);
	else
		calc->perp_wall_dist = (calc->side_dist_y - calc->delta_dist_y);
	calc->line_height = (int)(screenHeight / calc->perp_wall_dist);
	calc->draw_start = -calc->line_height / 2 + screenHeight / 2;
	if (calc->draw_start < 0)
		calc->draw_start = 0;
	calc->draw_end = calc->line_height / 2 + screenHeight / 2;
	if (calc->draw_end >= screenHeight)
		calc->draw_end = screenHeight - 1;
}
