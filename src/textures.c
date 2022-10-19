#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

static int		find_pixel(const t_img *src, int x, int y);

int	init_txtrs(void *mlx, char *paths[], t_txtr ts[])
{
	int	i;
	
	if (!*paths)
		return (1);
	i = -1;
	while (paths[++i])
	{
		ts[i].img.img = mlx_xpm_file_to_image(mlx, paths[i],
			&ts[i].img_width, &ts[i].img_height);
		if (!ts[i].img.img)
			return (2);
		// handle error -> clean all images
		ts[i].img.addr = mlx_get_data_addr(ts[i].img.img, &ts[i].img.bits_per_pixel, &ts[i].img.line_length, &ts[i].img.endian);
		// handle error
	}
	return (0);
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

static int	find_pixel(const t_img *src, int x, int y)
{
	return (*(int *) (src->addr + y * src->line_length + x * (src->bits_per_pixel / 8)));
}