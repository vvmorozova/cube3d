#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graphics.h"

// /*

char world_map[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_c_f(t_mlx *mlx_data);
void	draw_txt_line(t_img *src, t_img *dst, int start, int end, int height, int screen_x, int tex_x);
int		find_pixel(const t_img *src, int x, int y);

// void	redraw(t_mlx *mlx_data, t_data *data)
void	redraw(t_all_data *a_data)
{
	// mlx_data->img.img = mlx_new_image(mlx_data->mlx, screenWidth, screenHeight);
	// mlx_data->img.addr = mlx_get_data_addr(mlx_data->img.img, &mlx_data->img.bits_per_pixel, &mlx_data->img.line_length,
	// 							&mlx_data->img.endian);

	t_mlx	*mlx_data = a_data->mlx_data;
	t_data	*data = a_data->data;
	t_img	*txt;
	// t_img	*txt = a_data->txt;

	draw_c_f(mlx_data);

	for (int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double) screenWidth - 1; //x-coordinate in camera space
		double ray_dir_x = data->dir_x + data->plane_x * camera_x;
		double ray_dir_y = data->dir_y + data->plane_y * camera_x;
	
		//which box of the map we're in
		int map_x = (int)data->pos_x ;
		int map_y = (int)data->pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		double perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
	
		//calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->pos_x  - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->pos_x ) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
			}
			else
			{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
			}
			//Check if ray has hit a wall
			if (world_map[map_x][map_y] > 0)
				hit = 1;
		} 

		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		//Calculate height of line to draw on screen
		int line_height = (int)(screenHeight / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + screenHeight / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + screenHeight / 2;
		if (draw_end >= screenHeight)
			draw_end = screenHeight - 1;


		//choose wall color
		int color;
		switch(world_map[map_x][map_y])
		{
			case 1:  color = RED;  break; //red
			case 2:  color = GREEN;  break; //green
			case 3:  color = BLUE;   break; //blue
			case 4:  color = BLUE;  break; //white
			default: color = YELLOW; break; //yellow
		}

		//give x and y sides different brightness
		// if (side == 1)
		// {
		// 	color = color / 2;
		// }

		// /*
		// textures
		//calculate value of wallX
		double wall_x; //where exactly the wall was hit
		if (side == 0)
			wall_x = data->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = data->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		int tex_x = (int) (wall_x * (double) TEX_WIDTH);
		if (side == 0 && ray_dir_x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;

		//calculate texture
		if (side == 0) // x side -> NS
		{
			if (ray_dir_x > 0)
				txt = &((a_data->txtrs + 0)->img);
			else
				txt = &((a_data->txtrs + 1)->img);
		}
		else // y side -> EW
		{
			if (ray_dir_y > 0)
				txt = &((a_data->txtrs + 2)->img);
			else
				txt = &((a_data->txtrs + 3)->img);
		}

		draw_txt_line(txt, &mlx_data->img, draw_start, draw_end, line_height, x, tex_x);

/*
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEX_HEIGHT / line_height;
		// double step = 1.0 * line_height / TEX_HEIGHT;
		// Starting texture coordinate
		// double tex_pos = (draw_start - screenHeight / 2 + line_height / 2) * step;
		int	y = draw_start;
		for (double h = 0; h < (double)TEX_HEIGHT; h = h + step)
		// for (int y = draw_start; y < draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			double tex_y = (double)h; // + step;
			printf("tex_y %lf step %f text_x %d\n", tex_y, step, tex_x);
			
			// int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
			// tex_pos += step;
			// color = *(unsigned int *) (txt.addr + (tex_y * txt.line_length));
			// color = *(unsigned int *) (txt.addr + (tex_y * 64));
			color = *(unsigned int *) (txt.addr + ((int)tex_y * 64 + tex_x * (txt.bits_per_pixel / 8)));
			my_mlx_pixel_put(&mlx_data->img, x, y, color);
			// color = *(txt.addr + (tex_y * txt.line_length + tex_x * (txt.bits_per_pixel / 8)));

			y++; // delete

		}


		// */

		//draw the pixels of the stripe as a vertical line
		// verLine(&mlx_data->img, x, draw_start, draw_end, color);

	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, mlx_data->img.img, 0, 0);
	// mlx_destroy_image(mlx_data->mlx, mlx_data->img.img);

}
// */

void	draw_c_f(t_mlx *mlx_data)
{
	unsigned int	*dst;
	unsigned int		i;

	dst = (unsigned int *) mlx_data->img.addr;
	i = screenWidth * screenHeight / 2 + 1;
	while (--i > 0)
		*(unsigned int *) dst++ = CEILING;
	i = screenWidth * screenHeight / 2 + 1;
	while (--i > 0) {
		*(unsigned int *) dst++ = FLOOR;
	}
}



void	draw_txt_line(t_img *src, t_img *dst, int start, int end, int height, int screen_x, int tex_x)
{
	int	color;
	double	step = 1.0 * TEX_HEIGHT / height;
	double tex_y = (start - screenHeight / 2 + height / 2) * step;;
	// double	tex_y = 0;

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