/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <bsarai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:22:26 by bsarai            #+#    #+#             */
/*   Updated: 2022/10/19 18:53:07 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

static int		find_pixel(const t_img *src, int x, int y);
static t_img	*choose_txt(t_all_data *a_data, t_calc *calc);

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
		ts[i].img.addr = mlx_get_data_addr(ts[i].img.img,
				&ts[i].img.bits_per_pixel,
				&ts[i].img.line_length, &ts[i].img.endian);
	}
	return (0);
}

t_img	*calc_txt(t_all_data *a_data, t_calc *calc)
{
	t_img	*txt;
	t_data	*data;

	data = a_data->data;
	if (calc->side == 0)
		calc->wall_x = data->pos_y + calc->perp_wall_dist * calc->ray_dir_y;
	else
		calc->wall_x = data->pos_x + calc->perp_wall_dist * calc->ray_dir_x;
	calc->wall_x -= floor((calc->wall_x));
	calc->tex_x = (int)(calc->wall_x * (double) TEX_WIDTH);
	if (calc->side == 0 && calc->ray_dir_x > 0)
		calc->tex_x = TEX_WIDTH - calc->tex_x - 1;
	if (calc->side == 1 && calc->ray_dir_y < 0)
		calc->tex_x = TEX_WIDTH - calc->tex_x - 1;
	txt = choose_txt(a_data, calc);
	return (txt);
}

static t_img	*choose_txt(t_all_data *a_data, t_calc *calc)
{
	t_img	*txt;

	if (calc->side == 0)
	{
		if (calc->ray_dir_x > 0)
			txt = &((a_data->txtrs + 0)->img);
		else
			txt = &((a_data->txtrs + 1)->img);
	}
	else
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
	double	step;
	double	tex_y;
	int		screen_y;
	int		color;

	step = 1.0 * TEX_HEIGHT / calc->line_height;
	tex_y = (calc->draw_start - SCREEN_HEIGHT / 2
			+ calc->line_height / 2) * step;
	screen_y = calc->draw_start;
	while (screen_y < calc->draw_end)
	{
		color = find_pixel(src, calc->tex_x, (int)tex_y);
		tex_y += step;
		my_mlx_pixel_put(dst, screen_x, screen_y, color);
		screen_y++;
	}
}

static int	find_pixel(const t_img *src, int x, int y)
{
	return (*(int *)(src->addr + y * src->line_length
		+ x * (src->bits_per_pixel / 8)));
}
