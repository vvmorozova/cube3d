#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cube3d.h"

# ifndef screenWidth
#define screenWidth 640
# endif

# ifndef screenHeight
#define screenHeight 480
# endif

# ifndef TRANSPARENCY
#  define TRANSPARENCY 0
# endif

# ifndef CEILING
#  define CEILING 0xFCF3CF
# endif

# ifndef FLOOR
#  define FLOOR 0x34495E
# endif

# ifndef ROT_SPEED
#  define ROT_SPEED 0.5
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 0.7
# endif

# ifndef TEX_WIDTH
#  define TEX_WIDTH 64
# endif

# ifndef TEX_HEIGHT
#  define TEX_HEIGHT 64
# endif

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

typedef struct	s_txtr {
	t_img	img;
	char	*relative_path;
	int		img_width;
	int		img_height;
}			t_txtr;

typedef struct	s_all_data {
	t_mlx	*mlx_data;
	t_data	*data;
	t_txtr	txtrs[4];
	t_parsed_map	*map_data;
}			t_all_data;

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

void	redraw(t_all_data *a_data);

	// calc_functions.c
void	init_calc(t_data *data, t_calc *calc, int x);
void	calc_step_and_side_dist(t_data *data, t_calc *calc);
void	dda(char	**world_map, t_calc *calc);
void	calc_line_height(t_calc *calc);
t_img	*calc_txt(t_all_data *a_data, t_calc *calc);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

	// textures
int		init_txtrs(void *mlx, char *paths[], t_txtr ts[]);

	// event-handling
int		key_pressed(int keycode, t_all_data *a_data);
void	rot_left(t_data *d);
void	rot_right(t_data *d);
	// move_functions.c
void	move_back(t_data *d, char	**world_map);
void	move_front(t_data *d, char	**world_map);
void	move_left(t_data *d, char	**world_map);
void	move_right(t_data *d, char	**world_map);

int  close_window(t_mlx *mlx_data);
#endif
