#ifndef CUBE3D_H
#define CUBE3D_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct s_map_size{
	int	x;
	int	y;
}	t_map_size;

typedef struct s_path_to_textures{
	int	n;
	int	s;
	int	w;
	int	e;
}   t_path_to_textures;

typedef struct s_parsed_map{
	t_path_to_textures	texture;
	t_map_size			size;
	int					direction;
	int					**map;

}	t_parsed_map;

// PARSER
int parse(int argc, char **argv);
int write_err_and_exit(char *err);
int is_space(char c);
char	*get_next_line(int fd);

#endif