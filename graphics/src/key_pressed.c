#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"

int	key_pressed(int keycode, t_all_data *a_data)
{
	t_data	*d;

	d = a_data->data;
	if (keycode == 53)
	{
		mlx_destroy_image(a_data->mlx_data->mlx, a_data->mlx_data->img.img);
		mlx_destroy_window(a_data->mlx_data->mlx, a_data->mlx_data->mlx_win);
		exit(0);
	}
	if (keycode == 123)
		rot_left(d);
	else if (keycode == 124)
		rot_right(d);
	else if (keycode == 125 || keycode == 1)
		move_back(d, a_data->map_data->map);
	else if (keycode == 126 || keycode == 13)
		move_front(d, a_data->map_data->map);
	else if (keycode == 0)
		move_left(d, a_data->map_data->map);
	else if (keycode == 2)
		move_right(d, a_data->map_data->map);
	redraw(a_data);
	return (0);
}

void	rot_left(t_data *d)
{
	double	rot_speed = ROT_SPEED;
	double old_dir_x = d->dir_x;
	double old_plane_x = d->plane_x;

	d->dir_x = d->dir_x * cos(rot_speed) - d->dir_y * sin(rot_speed);
	d->dir_y = old_dir_x * sin(rot_speed) + d->dir_y * cos(rot_speed);
	d->plane_x = d->plane_x * cos(rot_speed) - d->plane_y * sin(rot_speed);
	d->plane_y = old_plane_x * sin(rot_speed) + d->plane_y * cos(rot_speed);
}

void	rot_right(t_data *d)
{
	double	rot_speed = ROT_SPEED;
	double old_dir_x = d->dir_x;
	double old_plane_x = d->plane_x;

	d->dir_x = d->dir_x * cos(-rot_speed) - d->dir_y * sin(-rot_speed);
	d->dir_y = old_dir_x * sin(-rot_speed) + d->dir_y * cos(-rot_speed);
	d->plane_x = d->plane_x * cos(-rot_speed) - d->plane_y * sin(-rot_speed);
	d->plane_y = old_plane_x * sin(-rot_speed) + d->plane_y * cos(-rot_speed);
}
