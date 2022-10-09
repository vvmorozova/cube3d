/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:40:04 by eward             #+#    #+#             */
/*   Updated: 2022/10/08 19:40:06 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	init_g_map(t_parsed_map *g_map)
{
	g_map->texture.n = -1;
	g_map->texture.s = -1;
	g_map->texture.e = -1;
	g_map->texture.w = -1;
	g_map->texture.e = -1;
	g_map->ceiling.r = -1;
	g_map->ceiling.g = -1;
	g_map->ceiling.b = -1;
	g_map->floor.r = -1;
	g_map->floor.g = -1;
	g_map->floor.b = -1;
	g_map->map = NULL;
}

int	check_if_g_map_ready(t_parsed_map *g_map)
{
	if (g_map->texture.n == -1 || g_map->texture.s == -1
			|| g_map->texture.w == -1 || g_map->texture.w == -1)
		return (-1);
	if (g_map->ceiling.r == -1 || g_map->ceiling.g == -1
			|| g_map->ceiling.b == -1)
		return (-1);
	if (g_map->floor.r == -1 || g_map->floor.g == -1
			|| g_map->floor.b == -1)
		return (-1);
	return (0);
}

int	parse(int argc, char **argv, t_parsed_map *g_map)
{
	int	fd;
	char	*line;

	init_g_map(g_map);
	if (argc == 1)
		write_err_and_exit("No map");
	else if (argc > 2)
		write_err_and_exit("Too many args");
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		write_err_and_exit("Map not found");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
		write_err_and_exit("File is not .cub");
	line = get_next_line(fd);
	while (line && check_if_g_map_ready(g_map) == -1)
	{
		if (check_textures(line, g_map) == -1 && check_flat(line, g_map) == -1)
			write_err_and_exit("Id is not recognized");
		free(line);
		line = get_next_line(fd);
	}
	if (check_if_g_map_ready(g_map) == 0)
	{
	}
	close(fd);
	return (0);
}
