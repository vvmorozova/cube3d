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
	t_mlx	*mlx_data;
	t_data	*data;
	t_img	*txt;
	t_calc	calc;
	int		x;

	mlx_data = a_data->mlx_data;
	data = a_data->data;
	x = 0;
	draw_c_f(mlx_data, a_data->map_data);
	while (x < SCREEN_WIDTH)
	{
		init_calc(data, &calc, x);
		dda(a_data->map_data->map, &calc);
		calc_line_height(&calc);
		txt = calc_txt(a_data, &calc);
		draw_txt_line(txt, &mlx_data->img, &calc, x);
		x++;
	}
	mlx_put_image_to_window(mlx_data->mlx,
		mlx_data->mlx_win, mlx_data->img.img, 0, 0);
}

int	create_rgb(t_rgb color)
{
	return (TRANSPARENCY << 24 | color.r << 16
		| color.g << 8 | color.b);
}

void	draw_c_f(t_mlx *mlx_data, t_parsed_map *m)
{
	unsigned int	*dst;
	unsigned int	i;
	int				ceil;
	int				floor;

	ceil = create_rgb(m->ceiling);
	floor = create_rgb(m->floor);
	dst = (unsigned int *) mlx_data->img.addr;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*(unsigned int *) dst++ = ceil;
	i = SCREEN_WIDTH * SCREEN_HEIGHT / 2 + 1;
	while (--i > 0)
		*(unsigned int *) dst++ = floor;
}
