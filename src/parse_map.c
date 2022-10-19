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

#include "cube3d.h"

int	check_map(t_parsed_map *g_map)
{
	check_lines(g_map);
	check_columns(g_map);
	return (0);
}

void	player_amount(t_parsed_map *g_map, int i, int j, char *line)
{
	g_map->map[j][i] = is_allowed(line[i]);
	if (is_allowed(line[i]) > 64 && is_allowed(line[i]) < 91)
	{
		if (!g_map->direction)
			g_map->direction = line[i];
		else
			write_err_and_exit("More than one player");
		g_map->pos.x = j;
		g_map->pos.y = i;
		g_map->map[j][i] = 0;
	}
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
		i = -1;
		while (line[++i] && is_allowed(line[i]) != -1)
			player_amount(g_map, i, j, line);
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
