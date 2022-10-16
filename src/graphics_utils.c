#include "graphics.h"
#include <mlx.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	verLine(t_img *img, int x, int draw_start, int draw_end, int color)
{
	while (draw_start < draw_end)
	{
		my_mlx_pixel_put(img, x, draw_start, color);
		draw_start++;
	}
}

int  close_window(t_mlx *mlx_data)
{
  mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
  exit(0);
  return (0);
}
