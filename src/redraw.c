#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"
#include "cube3d.h"

void	draw_c_f(t_mlx *mlx_data, t_parsed_map *map);

int		create_rgb(t_rgb color);

void	redraw(t_all_data *a_data)
{
	t_mlx	*mlx_data = a_data->mlx_data;
	t_data	*data = a_data->data;
	t_img	*txt;
	t_calc	calc;

	draw_c_f(mlx_data, a_data->map_data);
	// printf("x %f y %f; dirX %f dirY %f\n", data->pos_x, data->pos_y, data->dir_x, data->dir_y);	

	for (int x = 0; x < screenWidth; x++)
	{
		init_calc(data, &calc, x);
		dda(a_data->map_data->map, &calc);
		calc_line_height(&calc);
		txt = calc_txt(a_data, &calc);
		draw_txt_line(txt, &mlx_data->img, &calc, x);
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, mlx_data->img.img, 0, 0);
}

int		create_rgb(t_rgb color)
{
	return (TRANSPARENCY << 24 | color.r << 16 |
			color.g << 8 | color.b);
}


void	draw_c_f(t_mlx *mlx_data, t_parsed_map *m)
{
	unsigned int	*dst;
	unsigned int		i;
	int	ceil;
	int	floor;

	ceil = create_rgb(m->ceiling);
	floor = create_rgb(m->floor);
	dst = (unsigned int *) mlx_data->img.addr;
	i = screenWidth * screenHeight / 2 + 1;
	while (--i > 0)
		*(unsigned int *) dst++ = ceil;
	i = screenWidth * screenHeight / 2 + 1;
	while (--i > 0)
		*(unsigned int *) dst++ = floor;
}