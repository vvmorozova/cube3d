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

#include "cube3d.h"

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

void	print_map(t_parsed_map *g_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < g_map->size.y)
	{
		i = 0;
		while (i < g_map->size.x)
		{
			printf("%2d ", g_map->map[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

int	open_map(int argc, char **argv)
{
	int		fd;

	if (argc == 1)
		write_err_and_exit("No map");
	else if (argc > 2)
		write_err_and_exit("Too many args");
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		write_err_and_exit("Map not found");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
		write_err_and_exit("File is not .cub");
	return (fd);
}

void	replace_spaces(t_parsed_map *g_map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < g_map->size.y)
	{
		i = -1;
		while (++i < g_map->size.x)
			if (g_map->map[j][i] == ' ')
				g_map->map[j][i] = 0;
	}
}

int	parse(int argc, char **argv, t_parsed_map *g_map)
{
	int		fd;
	char	*line;
	int		until_map;
	int		i;

	until_map = 0;
	init_g_map(g_map);
	fd = open_map(argc, argv);
	line = get_next_line(fd);
	while (line && check_if_g_map_ready(g_map) == -1)
	{
		i = 0;
		while (is_space(*(line + i)))
			i++;
		if (*(line + i))
			if (check_textures(line + i, g_map) == -1 && check_flat(line + i, g_map) == -1)
				write_err_and_exit("Id is not recognized or more than one equal id");
		free(line);
		line = get_next_line(fd);
		until_map++;
	}
	if (line)
		free(line);
	fd = count_h_w(fd, until_map, argv[1], g_map);
	if (check_if_g_map_ready(g_map) == 0)
		parse_map(fd, g_map);
	else
		write_err_and_exit("Not enough data");
	replace_spaces(g_map);
	print_map(g_map);
	close(fd);
	return (0);
}
