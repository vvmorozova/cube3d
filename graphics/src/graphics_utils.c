#include "graphics.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	verLine(t_data *img, int x, int drawStart, int drawEnd, int color)
{
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(img, x, drawStart, color);
		drawStart++;
	}
}
