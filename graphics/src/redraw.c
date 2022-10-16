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



// camera_x - x-coordinate in camera space
// ray_dir_x, ray_dir_y - position of the ray

// map_x, map_y - which box of the map we're in

// side_dist_x, side_dist_y - length of ray from 
// current position to next x or y-side

// delta_dist_x, delta_dist_y - length of ray from
// one x or y-side to next x or y-side

// perp_wall_dist - perpendicular distance projected
// on camera direction

// step_x, step_y - what direction to step in x or
// y-direction (either +1 or -1)

// hit - was there a wall hit?
// side - was a NS or a EW wall hit?

// wall_x - where exactly the wall was hit

// line_height - height of line to draw on screen

// draw_start, draw_end - lowest and highest pixel
// to fill in current stripe

// tex_x - x coordinate of texture
typedef struct	s_calc {
	
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;

	int map_x;
	int map_y;

	double side_dist_x;
	double side_dist_y;

	double delta_dist_x;
	double delta_dist_y;

	double perp_wall_dist;

	int step_x;
	int step_y;

	int hit;
	int	side;

	double wall_x;

	int line_height; 
	int draw_start;
	int draw_end;

	int	tex_x;
}			t_calc;

void	init_calc(t_data *data, t_calc *calc, int x);
void	calc_step_and_side_dist(t_data *data, t_calc *calc);
void	dda(t_calc *calc);
void	calc_line_height(t_calc *calc);
t_img	*calc_txt(t_all_data *a_data, t_calc *calc);

void	draw_c_f(t_mlx *mlx_data);
void	draw_txt_line(t_img *src, t_img *dst, t_calc *calc, int screen_x);
int		find_pixel(const t_img *src, int x, int y);


void	redraw(t_all_data *a_data)
{
	t_mlx	*mlx_data = a_data->mlx_data;
	t_data	*data = a_data->data;
	t_img	*txt;
	t_calc	calc;

	draw_c_f(mlx_data);

	// printf("x %f y %f; dirX %f dirY %f\n", data->pos_x, data->pos_y, data->dir_x, data->dir_y);	

	for (int x = 0; x < screenWidth; x++)
	{
		init_calc(data, &calc, x);
		dda(&calc);
		calc_line_height(&calc);
		txt = calc_txt(a_data, &calc);
		draw_txt_line(txt, &mlx_data->img, &calc, x);
	}
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->mlx_win, mlx_data->img.img, 0, 0);
}

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

void	init_calc(t_data *data, t_calc *calc, int x)
{
		calc->camera_x = 2 * x / (double) screenWidth - 1;
		calc->ray_dir_x = data->dir_x + data->plane_x * calc->camera_x;
		calc->ray_dir_y = data->dir_y + data->plane_y * calc->camera_x;
		calc->map_x = (int)data->pos_x ;
		calc->map_y = (int)data->pos_y;
		if (calc->ray_dir_x == 0)
			calc->delta_dist_x = 1e30;
		else
			calc->delta_dist_x = fabs(1 / calc->ray_dir_x);
		if (calc->ray_dir_y == 0)
			calc->delta_dist_y = 1e30;
		else
			calc->delta_dist_y = fabs(1 / calc->ray_dir_y);
		calc->hit = 0;
		calc_step_and_side_dist(data, calc);
}

void	calc_step_and_side_dist(t_data *data, t_calc *calc)
{
	if (calc->ray_dir_x < 0)
	{
		calc->step_x = -1;
		calc->side_dist_x = (data->pos_x  - calc->map_x) * calc->delta_dist_x;
	}
	else
	{
		calc->step_x = 1;
		calc->side_dist_x = (calc->map_x + 1.0 - data->pos_x ) * calc->delta_dist_x;
	}
	if (calc->ray_dir_y < 0)
	{
		calc->step_y = -1;
		calc->side_dist_y = (data->pos_y - calc->map_y) * calc->delta_dist_y;
	}
	else
	{
		calc->step_y = 1;
		calc->side_dist_y = (calc->map_y + 1.0 - data->pos_y) * calc->delta_dist_y;
	}
}

void	dda(t_calc *calc)
{
	while (calc->hit == 0)
	{
		if (calc->side_dist_x < calc->side_dist_y)
		{
			calc->side_dist_x += calc->delta_dist_x;
			calc->map_x += calc->step_x;
			calc->side = 0;
		}
		else
		{
			calc->side_dist_y += calc->delta_dist_y;
			calc->map_y += calc->step_y;
			calc->side = 1;
		}
		if (world_map[calc->map_x][calc->map_y] > 0)
			calc->hit = 1;
	} 
}

void	calc_line_height(t_calc *calc)
{
	if (calc->side == 0)
		calc->perp_wall_dist = (calc->side_dist_x - calc->delta_dist_x);
	else
		calc->perp_wall_dist = (calc->side_dist_y - calc->delta_dist_y);
	calc->line_height = (int)(screenHeight / calc->perp_wall_dist);
	calc->draw_start = -calc->line_height / 2 + screenHeight / 2;
	if (calc->draw_start < 0)
		calc->draw_start = 0;
	calc->draw_end = calc->line_height / 2 + screenHeight / 2;
	if (calc->draw_end >= screenHeight)
		calc->draw_end = screenHeight - 1;
}

t_img	*calc_txt(t_all_data *a_data, t_calc *calc)
{
	t_img	*txt;
	t_data	*data = a_data->data;

	// textures
	//calculate value of wallX
	// calc.wall_x; //where exactly the wall was hit
	if (calc->side == 0)
		calc->wall_x = data->pos_y + calc->perp_wall_dist * calc->ray_dir_y;
	else
		calc->wall_x = data->pos_x + calc->perp_wall_dist * calc->ray_dir_x;
	calc->wall_x -= floor((calc->wall_x));

	//x coordinate on the texture
	calc->tex_x = (int) (calc->wall_x * (double) TEX_WIDTH);
	if (calc->side == 0 && calc->ray_dir_x > 0)
		calc->tex_x = TEX_WIDTH - calc->tex_x - 1;
	if (calc->side == 1 && calc->ray_dir_y < 0)
		calc->tex_x = TEX_WIDTH - calc->tex_x - 1;

	//calculate texture
	if (calc->side == 0) // x side -> NS
	{
		if (calc->ray_dir_x > 0)
			txt = &((a_data->txtrs + 0)->img);
		else
			txt = &((a_data->txtrs + 1)->img);
	}
	else // y side -> EW
	{
		if (calc->ray_dir_y > 0)
			txt = &((a_data->txtrs + 2)->img);
		else
			txt = &((a_data->txtrs + 3)->img);
	}
	return (txt);
}


void	draw_txt_line(t_img *src, t_img *dst, t_calc *calc, int screen_x)
{
	int	color;
	double	step = 1.0 * TEX_HEIGHT / calc->line_height;
	double tex_y = (calc->draw_start - screenHeight / 2 + calc->line_height / 2) * step;;

	// repeat for all pixels from start to end
	for (int screen_y = calc->draw_start; screen_y < calc->draw_end; screen_y++) {

	// locate src pixel
	color = find_pixel(src, calc->tex_x, (int)tex_y);
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