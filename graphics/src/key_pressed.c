#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"


char world_map[mapWidth][mapHeight];

int	key_pressed(int keycode, t_all_data *a_data)
{
	double	move_speed = MOVE_SPEED;
	double	rot_speed = ROT_SPEED;


	if (keycode == 53)
	{
		mlx_destroy_image(a_data->mlx_data->mlx, a_data->mlx_data->img.img);
		mlx_destroy_window(a_data->mlx_data->mlx, a_data->mlx_data->mlx_win);
		exit(0);
	}
	
	t_data	*d;
	d = a_data->data;

	if (keycode == 123)
	{
		double old_dir_x = d->dir_x;
		d->dir_x = d->dir_x * cos(rot_speed) - d->dir_y * sin(rot_speed);
		d->dir_y = old_dir_x * sin(rot_speed) + d->dir_y * cos(rot_speed);
		double old_plane_x = d->plane_x;
		d->plane_x = d->plane_x * cos(rot_speed) - d->plane_y * sin(rot_speed);
		d->plane_y = old_plane_x * sin(rot_speed) + d->plane_y * cos(rot_speed);
	}
	else if (keycode == 124)
	{
		double old_dir_x = d->dir_x;
		d->dir_x = d->dir_x * cos(-rot_speed) - d->dir_y * sin(-rot_speed);
		d->dir_y = old_dir_x * sin(-rot_speed) + d->dir_y * cos(-rot_speed);
		double old_plane_x = d->plane_x;
		d->plane_x = d->plane_x * cos(-rot_speed) - d->plane_y * sin(-rot_speed);
		d->plane_y = old_plane_x * sin(-rot_speed) + d->plane_y * cos(-rot_speed);
	}
	else if (keycode == 125 || keycode == 1)
	{
		if (!world_map[(int) (d->pos_x - d->dir_x * move_speed)][(int) d->pos_y])
			d->pos_x -= d->dir_x * move_speed;
		if (!world_map[(int) d->pos_x][(int) (d->pos_y - d->dir_y * move_speed)])
			d->pos_y -= d->dir_y * move_speed;
	}
	else if (keycode == 126 || keycode == 13)
	{
		if (!world_map[(int) (d->pos_x + d->dir_x * move_speed)][(int) d->pos_y])
			d->pos_x += d->dir_x * move_speed;
		if (!world_map[(int) d->pos_x][(int) (d->pos_y + d->dir_y * move_speed)])
			d->pos_y += d->dir_y * move_speed;
	}
	else if (keycode == 0) // a
	{

	}
	else if (keycode == 2) // d
	{
		
	}
	redraw(a_data->mlx_data, a_data->data);
	return (0);
}
