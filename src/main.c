#include <mlx.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"
#include "cube3d.h"

static void	choose_dir_e_w(t_data *data, char dir);
static void	choose_dir(t_data	*data, char dir);
static void	all_data_init(t_all_data *a_data, t_mlx	*mlx_data,
				t_parsed_map	*g_map, t_data *data);

int	main(int argc, char **argv)
{
	t_parsed_map	g_map;
	t_mlx			mlx_data;
	t_data			data;
	t_all_data		all_data;

	parse(argc, argv, &g_map);
	all_data_init(&all_data, &mlx_data, &g_map, &data);
	redraw(&all_data);
	mlx_hook(mlx_data.mlx_win, 17, 1L << 17, close_window, &mlx_data);
	mlx_key_hook(mlx_data.mlx_win, key_pressed, &all_data);
	mlx_loop(mlx_data.mlx);
}

static void	all_data_init(t_all_data *a_data, t_mlx	*mlx_data,
		t_parsed_map	*g_map, t_data *data)
{
	char	**txts_path;

	txts_path = g_map->txts_path;
	mlx_data->mlx = mlx_init();
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub");
	mlx_data->img.img = mlx_new_image(mlx_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_data->img.addr = mlx_get_data_addr(mlx_data->img.img,
			&mlx_data->img.bits_per_pixel, &mlx_data->img.line_length,
			&mlx_data->img.endian);
	a_data->mlx_data = mlx_data;
	data->pos_x = g_map->pos.x;
	data->pos_y = g_map->pos.y;
	choose_dir(data, g_map->direction);
	a_data->data = data;
	a_data->map_data = g_map;
	if (init_txtrs(mlx_data->mlx, txts_path, a_data->txtrs))
	{
		free_txt_paths(txts_path);
		mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
		exit(1);
	}
	free_txt_paths(txts_path);
}

static void	choose_dir(t_data	*data, char dir)
{
	if (dir == 'S' || dir == 'N')
	{
		data->plane_x = 0;
		data->dir_y = 0;
		if (dir == 'S')
		{
			data->dir_x = 1;
			data->plane_y = -0.66;
		}
		if (dir == 'N')
		{
			data->dir_x = -1;
			data->plane_y = 0.66;
		}
	}
	choose_dir_e_w(data, dir);
}

static void	choose_dir_e_w(t_data *data, char dir)
{
	if (dir == 'E' || dir == 'W')
	{
		data->plane_y = 0;
		data->dir_x = 0;
		if (dir == 'E')
		{
			data->dir_y = 1;
			data->plane_x = 0.66;
		}
		if (dir == 'W')
		{
			data->dir_y = -1;
			data->plane_x = -0.66;
		}
	}
}
