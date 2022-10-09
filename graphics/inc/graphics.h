#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	verLine(t_img *img, int x, int drawStart, int drawEnd, int color);


#endif
