#include "graphics.h"

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
