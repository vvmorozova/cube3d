/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_holes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:28:07 by eward             #+#    #+#             */
/*   Updated: 2022/10/16 12:28:09 by eward            ###   ########.fr       */
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
