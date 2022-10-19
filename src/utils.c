/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:28:28 by eward             #+#    #+#             */
/*   Updated: 2022/10/16 12:28:30 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdlib.h>

int	write_err_and_exit(char *err)
{
	printf("Error\n%s\n", err);
	exit(0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\n'
		|| c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

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
	g_map->direction = 0;
	g_map->map = NULL;
	g_map->txts_path[0] = NULL;
	g_map->txts_path[1] = NULL;
	g_map->txts_path[2] = NULL;
	g_map->txts_path[3] = NULL;
	g_map->txts_path[4] = NULL;
}

void	free_map(t_parsed_map *g_map)
{
	int	j;

	j = -1;
	while (++j < g_map->size.y)
		free(g_map->map[j]);
	free(g_map->map);
}
