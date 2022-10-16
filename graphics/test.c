#include <mlx.h>
#include <stdio.h>

#define TEX_HEIGHT 64

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);


void	draw_txt_line(t_img *src, t_img *dst, int start, int end, int height, int screen_x, int tex_x);

int	main(void)
{
	int	screen_width = 1920;
	int	screen_height = 1080;

	void	*mlx;
	void	*mlx_win;
	t_img	img;
	char	*relative_path = "./txts/redbrick.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screen_width, screen_height, "Hello world!");
	img.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	t_img	screen;
	screen.img = mlx_new_image(mlx, screen_width, screen_height);
	screen.addr = mlx_get_data_addr(screen.img, &screen.bits_per_pixel, &screen.line_length,
							&screen.endian);
	

	int	tex_height = img_height;
	int	tex_width = img_width;
	
	int	draw_start = 30;
	int	draw_end = 70;
	int	line_height = 40;
	int	screen_x = 50;
	// int	tex_x = 0;

	for (int tex_x = 0; tex_x < 100; tex_x++, screen_x++)
		draw_txt_line(&img, &screen, draw_start, draw_end, line_height, screen_x, tex_x);

	mlx_put_image_to_window(mlx, mlx_win, screen.img, 0, 0);
	mlx_loop(mlx);

}

int	find_pixel(const t_img *src, int x, int y);

void	draw_txt_line(t_img *src, t_img *dst, int start, int end, int height, int screen_x, int tex_x)
{
	int	color;
	double	step = 1.0 * TEX_HEIGHT / height;
	double	tex_y = 0;
	// repeat for all pixels from start to end
	for (int screen_y = start; screen_y < end; screen_y++) {

	// locate src pixel
	color = find_pixel(src, tex_x, (int)tex_y);
		// printf("tex_y is %f; color is %d\n", tex_y, color);
	tex_y += step;
	
	// draw src pixel to dst pixel
	my_mlx_pixel_put(dst, screen_x, screen_y, color);
	
	}

}

int	find_pixel(const t_img *src, int x, int y)
{
	return (*(int *) (src->addr + y * src->line_length + x * (src->bits_per_pixel / 8)));
}

// int offset = (y * line_length + x * (bits_per_pixel / 8));

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(int *) dst = color;
	// printf("color after writing %d\n", find_pixel(img, x, y));
}