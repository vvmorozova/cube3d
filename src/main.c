#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"
#include "cube3d.h"

// char world_map[mapWidth][mapHeight];

void	choose_dir(t_data	*data, char dir)
{
	if (dir == 'S' || dir == 'N')
	{
		data->plane_x = 0;
		data->plane_y = 0.66;
		data->dir_y = 0;
		if (dir == 'S')
			data->dir_x = 1;
		if (dir == 'N')
			data->dir_x = -1;
	}
	if (dir == 'E' || dir == 'W')
	{
		data->plane_x = 0.66;
		data->plane_y = 0;
		data->dir_x = 0;
		if (dir == 'E')
			data->dir_y = 1;
		if (dir == 'W')
			data->dir_y = -1;
	}
}

int	main(int argc, char **argv)
{
	t_parsed_map	g_map;
	// ft_bzero(&g_map, sizeof(t_parsed_map));
	parse(argc, argv, &g_map);

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
	// n s w e
	// P == E -> w
	// data init
	t_data	data;
	data.pos_x = g_map.pos.x,	data.pos_y = g_map.pos.y;
	// data.dir_x = 1,	data.dir_y = 0;
	choose_dir(&(data), g_map.direction);
	// data.plane_x = 0.66, data.plane_y = 0;

	t_all_data	all_data;
	all_data.mlx_data = &mlx_data;
	all_data.data = &data;
	all_data.map_data = &g_map;

	if (init_txtrs(mlx_data.mlx, txts_path, all_data.txtrs))
	{
		// clean paths
		// destroy main image
		mlx_destroy_window(mlx_data.mlx, mlx_data.mlx_win);
		exit(1);
	}
	
	// mlx_put_image_to_window(mlx_data.mlx, mlx_data.mlx_win, txtrs[3].img.img, 0, 0);


	redraw(&all_data);
	mlx_hook(mlx_data.mlx_win, 17, 1L << 17, close_window, &mlx_data);
	mlx_key_hook(mlx_data.mlx_win, key_pressed, &all_data);

	// mlx_destroy_image
	mlx_loop(mlx_data.mlx);
}

