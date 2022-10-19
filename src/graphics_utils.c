/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <bsarai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:07:42 by eward             #+#    #+#             */
/*   Updated: 2022/10/19 18:52:59 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <mlx.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	close_window(t_mlx *mlx_data)
{
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	exit(0);
	return (0);
}
