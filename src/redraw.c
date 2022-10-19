#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"
#include "cube3d.h"

void	draw_c_f(t_mlx *mlx_data, t_parsed_map *map);
void	draw_txt_line(t_img *src, t_img *dst, t_calc *calc, int screen_x);
int		find_pixel(const t_img *src, int x, int y);

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



t_img	*calc_txt(t_all_data *a_data, t_calc *calc)
{
	t_img	*txt;
	t_data	*data = a_data->data;

	// textures
	//calculate value of wallX
	// calc.wall_x; //where exactly the wall was hit
	if (calc->side == 0)
		calc->wall_x = data->pos_y + calc->perp_wall_dist * calc->ray_dir_y;
	else
		calc->wall_x = data->pos_x + calc->perp_wall_dist * calc->ray_dir_x;
	calc->wall_x -= floor((calc->wall_x));

	//x coordinate on the texture
	calc->tex_x = (int) (calc->wall_x * (double) TEX_WIDTH);
	if (calc->side == 0 && calc->ray_dir_x > 0)
		calc->tex_x = TEX_WIDTH - calc->tex_x - 1;
	if (calc->side == 1 && calc->ray_dir_y < 0)
		calc->tex_x = TEX_WIDTH - calc->tex_x - 1;

	//calculate texture
	if (calc->side == 0) // x side -> NS
	{
		if (calc->ray_dir_x > 0)
			txt = &((a_data->txtrs + 0)->img);
		else
			txt = &((a_data->txtrs + 1)->img);
	}
	else // y side -> EW
	{
		if (calc->ray_dir_y > 0)
			txt = &((a_data->txtrs + 2)->img);
		else
			txt = &((a_data->txtrs + 3)->img);
	}
	return (txt);
}


void	draw_txt_line(t_img *src, t_img *dst, t_calc *calc, int screen_x)
{
	int	color;
	double	step = 1.0 * TEX_HEIGHT / calc->line_height;
	double tex_y = (calc->draw_start - screenHeight / 2 + calc->line_height / 2) * step;;

	// repeat for all pixels from start to end
	for (int screen_y = calc->draw_start; screen_y < calc->draw_end; screen_y++) {

	// locate src pixel
	color = find_pixel(src, calc->tex_x, (int)tex_y);
		// printf("tex_y is %f; color is %d\n", tex_y, color);
	tex_y += step;
	
	// draw src pixel to dst pixel
	my_mlx_pixel_put(dst, screen_x, screen_y, color);
	
	}

}

int	find_pixel(const t_img *src, int x, int y)
{
	return (*(int *) (src->addr + y * src->line_length + x * (src->bits_per_pixel / 8)));
}