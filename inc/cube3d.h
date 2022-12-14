/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <bsarai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:24:59 by bsarai            #+#    #+#             */
/*   Updated: 2022/10/19 18:25:01 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "get_next_line.h"

typedef struct s_rgb{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map_size{
	int	x;
	int	y;
}	t_map_size;

typedef struct s_coordinates{
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_path_to_textures{
	int	n;
	int	s;
	int	w;
	int	e;
}   t_path_to_textures;

typedef struct s_parsed_map{
	t_path_to_textures	texture;
	char				*txts_path[5];
	t_map_size			size;
	t_rgb				ceiling;
	t_rgb				floor;
	int					direction;
	char				**map;
	t_coordinates		pos;
}	t_parsed_map;

// t_parsed_map	g_map;
// PARSER
char	*get_next_line(int fd);
int		parse(int argc, char **argv, t_parsed_map *g_map);
int		write_err_and_exit(char *err);
int		is_space(char c);
int		check_textures(char *line, t_parsed_map *g_map);
int		check_color(char *str, char *dir, t_rgb *flat);
int		check_flat(char *line, t_parsed_map *g_map);
int		count_h_w(int fd, int how_many_to_skip, char *filename, t_parsed_map *g_map);
int		parse_map(int fd, t_parsed_map *g_map);
int		is_allowed(int c);
int		allow(int c);
void	check_holes(t_parsed_map *g_map, int i, int j);
void	create_arr(t_parsed_map *g_map);
void	free_map(t_parsed_map *g_map);
void	free_textures(t_parsed_map *g_map);
void	check_lines(t_parsed_map *g_map);
void	check_columns(t_parsed_map *g_map);
void	init_g_map(t_parsed_map *g_map);

void	free_txt_paths(char *txt_path[]);
int		check_if_g_map_ready(t_parsed_map *g_map);

void	print_map(t_parsed_map *g_map);
#endif