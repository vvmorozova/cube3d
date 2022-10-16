#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"

void	move_back(t_data *d, char	**world_map)
{
	double	move_speed = MOVE_SPEED;

	if (!world_map[(int) (d->pos_x - d->dir_x * move_speed)][(int) d->pos_y])
		d->pos_x -= d->dir_x * move_speed;
	if (!world_map[(int) d->pos_x][(int) (d->pos_y - d->dir_y * move_speed)])
		d->pos_y -= d->dir_y * move_speed;
}

void	move_front(t_data *d, char **world_map)
{
	double	move_speed = MOVE_SPEED;

	if (!world_map[(int) (d->pos_x + d->dir_x * move_speed)][(int) d->pos_y])
		d->pos_x += d->dir_x * move_speed;
	if (!world_map[(int) d->pos_x][(int) (d->pos_y + d->dir_y * move_speed)])
		d->pos_y += d->dir_y * move_speed;
}

void	move_left(t_data *d, char **world_map)
{
	double	move_speed = MOVE_SPEED;

	if (!world_map[(int) (d->pos_x - d->plane_x * move_speed)][(int) d->pos_y])
		d->pos_x -= d->plane_x * move_speed;
	if (!world_map[(int) d->pos_x][(int) (d->pos_y - d->plane_y * move_speed)])
		d->pos_y -= d->plane_y * move_speed;
}

void	move_right(t_data *d, char **world_map)
{
	double	move_speed = MOVE_SPEED;

	if (!world_map[(int) (d->pos_x + d->plane_x * move_speed)][(int) d->pos_y])
		d->pos_x += d->plane_x * move_speed;
	if (!world_map[(int) d->pos_x][(int) (d->pos_y + d->plane_y * move_speed)])
		d->pos_y += d->plane_y * move_speed;
}