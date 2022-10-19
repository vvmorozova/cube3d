/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_g_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:49:34 by eward             #+#    #+#             */
/*   Updated: 2022/10/19 18:49:37 by eward            ###   ########.fr       */
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
