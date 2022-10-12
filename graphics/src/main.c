#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"


char world_map[mapWidth][mapHeight];




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

	char	*txts_path[5] = {"./txts/colorstone.xpm", "./txts/greystone.xpm", "./txts/purplestone.xpm", "./txts/redbrick.xpm", NULL};
	t_txtr txtrs[4];

	if (init_txtrs(mlx_data.mlx, txts_path, txtrs))
	{
		// clean paths
		// destroy main image
		mlx_destroy_window(mlx_data.mlx, mlx_data.mlx_win);
		exit(1);
	}
	// mlx_put_image_to_window(mlx_data.mlx, mlx_data.mlx_win, txtrs[3].img.img, 0, 0);

	// data init
	t_data	data;
	data.pos_x = 22,	data.pos_y = 12.0;
	data.dir_x = -1,	data.dir_y = 0;
	data.plane_x = 0, data.plane_y = 0.66;

	// redraw(&mlx_data, &data);
	redraw(&mlx_data, &data, &txtrs[3].img);

	t_all_data	all_data;
	all_data.mlx_data = &mlx_data;
	all_data.data = &data;
	all_data.txt = &txtrs[3].img;

	mlx_key_hook(mlx_data.mlx_win, key_pressed, &all_data);

	// mlx_destroy_image
	mlx_loop(mlx_data.mlx);
}

