#include "graphics.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	verLine(t_img *img, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(img, x, drawStart, color);
		drawStart++;
	}
}
