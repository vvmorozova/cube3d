/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:40:56 by eward             #+#    #+#             */
/*   Updated: 2022/10/15 20:40:57 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	check_lines(t_parsed_map *g_map)
{
	int		i;
	int		j;
	int		last_wall;

	j = -1;
	while (++j < g_map->size.y)
	{
		i = 0;
		while (i < g_map->size.x)
		{
			last_wall = -1;
			while (g_map->map[j][i] == ' ' && i < g_map->size.x)
				i++;
			if (i == g_map->size.x)
				break ;
			while (allow(g_map->map[j][i]) > 0 && i < g_map->size.x)
				last_wall = i++;
			if (last_wall == -1 && g_map->map[j][i] == 0 && i < g_map->size.x)
				write_err_and_exit("hole in wall");
			while (g_map->map[j][i] != 1 &&
					g_map->map[j][i] != ' ' && i < g_map->size.x)
				i++;
			check_holes(g_map, i, j);
		}
	}
}

void	check_holes2(t_parsed_map *g_map, int i, int j)
{
	if ((j == g_map->size.y && allow(g_map->map[j - 1][i]) == 0))
		write_err_and_exit("hole in wall");
	if (j == g_map->size.y)
		return ;
	if ((g_map->map[j][i] == ' ' && allow(g_map->map[j - 1][i]) == 0
		&& j < g_map->size.y))
		write_err_and_exit("hole in wall");
	if (j == g_map->size.y && allow(g_map->map[j - 1][i]) == 0)
		write_err_and_exit("hole in wall");
}

void	check_columns(t_parsed_map *g_map)
{
	int		i;
	int		j;
	int		last_wall;

	i = -1;
	while (++i < g_map->size.x)
	{
		j = 0;
		while (j < g_map->size.y)
		{
			last_wall = -1;
			while (j < g_map->size.y && g_map->map[j][i] == ' ')
				j++;
			if (j == g_map->size.y)
				break ;
			while (j < g_map->size.y && allow(g_map->map[j][i]) > 0)
				last_wall = j++;
			if (last_wall == -1 && g_map->map[j][i] == 0 && j < g_map->size.y)
				write_err_and_exit("hole in wall");
			while (j < g_map->size.y && g_map->map[j][i] != 1 &&
					g_map->map[j][i] != ' ')
				j++;
			check_holes2(g_map, i, j);
		}
	}
}

int	check_map(t_parsed_map *g_map)
{
	check_lines(g_map);
	check_columns(g_map);
	return (0);
}

int	parse_map(int fd, t_parsed_map *g_map)
{
	char	*line;
	int		i;
	int		j;

	create_arr(g_map);
	j = -1;
	line = get_next_line(fd);
	while (line && ++j < g_map->size.y)
	{
		i = 0;
		while (line[i] && is_allowed(line[i]) != -1)
		{
			g_map->map[j][i] = is_allowed(line[i]);
			if (is_allowed(line[i]) > 64 && is_allowed(line[i]) < 91)
			{
				if (!g_map->direction)
					g_map->direction = line[i];
				else
					write_err_and_exit("More than one player");
			}
			i++;
		}
		if (i < g_map->size.x - 1 && line[i] != '\n' && line[i] != '\0')
			write_err_and_exit("Wrong symbols in map");
		while (i < g_map->size.x)
			g_map->map[j][i++] = ' ';
		free(line);
		line = get_next_line(fd);
	}
	check_map(g_map);
	return (0);
}