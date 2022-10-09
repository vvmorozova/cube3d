#include <mlx.h>

#include <math.h>
#include <stdlib.h>

#include <stdio.h>


# ifndef RED
#  define  RED 0x00FF0000
# endif

# ifndef BLUE
#  define BLUE 0x0000ff
# endif

# ifndef YELLOW
#  define YELLOW 0xFF5733
# endif

# ifndef GREEN
#  define GREEN 0x75FF33
# endif

# ifndef WHITE
#  define WHITE 0xFFFFFF
# endif


#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

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




#include "graphics.h"



// void	redraw();

int	main(void)
{
	t_mlx	mlx_data;

	// void	*mlx;
	// void	*mlx_win;
	// t_img	img;

	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, 1920, 1080, "Hello world!");
	mlx_data.img.img = mlx_new_image(mlx_data.mlx, 1920, 1080);
	mlx_data.img.addr = mlx_get_data_addr(mlx_data.img.img, &mlx_data.img.bits_per_pixel, &mlx_data.img.line_length,
								&mlx_data.img.endian);
	
	// data init
	t_data	data;
	data.pos_x = 22,	data.pos_y = 12.0;
	data.dir_x = -1,	data.dir_y = 0;
	data.plane_x = 0, data.plane_y = 0.66;

	// redraw();
// /*
	for (int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double) screenWidth - 1; //x-coordinate in camera space
		double ray_dir_x = data.dir_x + data.plane_x * camera_x;
		double ray_dir_y = data.dir_y + data.plane_y * camera_x;
	
		//which box of the map we're in
		int map_x = (int)data.pos_x ;
		int map_y = (int)data.pos_y;

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
			side_dist_x = (data.pos_x  - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data.pos_x ) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data.pos_y) * delta_dist_y;
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
		if (side == 1)
		{
			color = color / 2;
		}

		//draw the pixels of the stripe as a vertical line
		verLine(&mlx_data.img, x, draw_start, draw_end, color);
		mlx_put_image_to_window(mlx_data.mlx, mlx_data.mlx_win, mlx_data.img.img, 0, 0);

	}
	// */

	// mlx_destroy_image
	mlx_loop(mlx_data.mlx);
}

/*
void	redraw(t_mlx *mlx, t_data *data)
{
	for (int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double) screenWidth - 1; //x-coordinate in camera space
		double ray_dir_x = data.dir_x + data.plane_x * camera_x;
		double ray_dir_y = data.dir_y + data.plane_y * camera_x;
	
		//which box of the map we're in
		int map_x = (int)data.pos_x ;
		int map_y = (int)data.pos_y;

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
			side_dist_x = (data.pos_x  - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data.pos_x ) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data.pos_y) * delta_dist_y;
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
		if (side == 1)
		{
			color = color / 2;
		}

		//draw the pixels of the stripe as a vertical line
		verLine(&mlx_data.img, x, draw_start, draw_end, color);
		mlx_put_image_to_window(mlx_data.mlx, mlx_data.mlx_win, mlx_data.img.img, 0, 0);

	}
}
*/