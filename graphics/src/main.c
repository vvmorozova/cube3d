#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"



int	main(void)
{
	t_mlx	mlx_data;

	// void	*mlx;
	// void	*mlx_win;
	// t_img	img;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, 1920, 1080, "Hello world!");
	mlx_data.img.img = mlx_new_image(mlx_data.mlx, 1920, 1080);
	mlx_data.img.addr = mlx_get_data_addr(mlx_data.img.img, &mlx_data.img.bits_per_pixel, &mlx_data.img.line_length,
								&mlx_data.img.endian);
	
	// data init
	t_data	data;
	data.pos_x = 22,	data.pos_y = 12.0;
	data.dir_x = -1,	data.dir_y = 0;
	data.plane_x = 0, data.plane_y = 0.66;

	redraw(&mlx_data, &data);

	// mlx_destroy_image
	mlx_loop(mlx_data.mlx);
}

