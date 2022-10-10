#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"


char world_map[mapWidth][mapHeight];

// typedef struct	s_all_data {
// 	t_mlx	*mlx_data;
// 	t_data	*data;
// }			t_all_data;

// int	key_pressed(int keycode, t_all_data *a_data);

int	main(void)
{
	t_mlx	mlx_data;

	// void	*mlx;
	// void	*mlx_win;
	// t_img	img;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, screenWidth, screenHeight, "Hello world!");
	mlx_data.img.img = mlx_new_image(mlx_data.mlx, screenWidth, screenHeight);
	mlx_data.img.addr = mlx_get_data_addr(mlx_data.img.img, &mlx_data.img.bits_per_pixel, &mlx_data.img.line_length,
								&mlx_data.img.endian);
	
	// data init
	t_data	data;
	data.pos_x = 22,	data.pos_y = 12.0;
	data.dir_x = -1,	data.dir_y = 0;
	data.plane_x = 0, data.plane_y = 0.66;

	redraw(&mlx_data, &data);

	// t_all_data	all_data;
	// all_data.mlx_data = &mlx_data;
	// all_data.data = &data;

	// mlx_key_hook(mlx_data.mlx_win, key_pressed, &all_data);


	// mlx_destroy_image
	mlx_loop(mlx_data.mlx);
}

// int	key_pressed(int keycode, t_all_data *a_data)
// {
// 	if (keycode == 53)
// 	{
// 		mlx_destroy_image(a_data->mlx_data->mlx, a_data->mlx_data->img.img);
// 		mlx_destroy_window(a_data->mlx_data->mlx, a_data->mlx_data->mlx_win);
// 		exit(0);
// 	}
// 	// if (keycode == 78)
// 	// {
// 	// 	if (data->zoom > 5)
// 	// 		data->zoom -= 5;
// 	// }
// 	// if (keycode == 69)
// 	// 	data->zoom += 5;
// 	// else if (keycode == 123)
	
// 	// else if (keycode == 124)
	
// 	// else if (keycode == 125)
	
// 	// else if (keycode == 126)
	
// 	// change_image(data);
// 	return (0);
// }
