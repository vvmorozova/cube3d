#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"


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

