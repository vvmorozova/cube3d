#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct	s_data {
	double pos_x; //start position
	double pos_y;//start position

	double dir_x; //initial direction vector
	double dir_y; //initial direction vector
	double plane_x; //the 2d raycaster version of camera plane
	double plane_y; //the 2d raycaster version of camera plane

}			t_data;

typedef struct	s_mlx {
	void	*mlx;
	void	*mlx_win;
	t_img	img;

}			t_mlx;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	verLine(t_img *img, int x, int drawStart, int drawEnd, int color);


#endif
