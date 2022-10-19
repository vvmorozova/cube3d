/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:04:29 by eward             #+#    #+#             */
/*   Updated: 2022/10/09 18:04:31 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	skip_comma(char **str)
{
	while (is_space(**str))
		(*str)++;
	if (**str != ',')
		return (-1);
	(*str)++;
	while (is_space(**str))
		(*str)++;
	return (0);
}

int	extract_color(char **str, int *color)
{
	int		n;

	n = 0;
	while (ft_isdigit(**str))
	{
		n = n * 10 + **str - '0';
		(*str)++;
	}
	if (n > 255)
		return (-1);
	*color = n;
	return (0);
}

int	check_colors(char *str, char id, t_rgb *flat)
{
	while (is_space(*str))
		str++;
	if (*str == id)
	{
		str++;
		while (is_space(*str))
			str++;
		extract_color(&str, &(flat->r));
		skip_comma(&str);
		extract_color(&str, &(flat->g));
		skip_comma(&str);
		extract_color(&str, &(flat->b));
		while (is_space(*str))
			str++;
		if (!*str)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	check_flat(char *line, t_parsed_map *g_map)
{
	if (g_map->ceiling.r < 0 && *line == 'C')
		check_colors(line, 'C', &(g_map->ceiling));
	else if (g_map->floor.r < 0 && *line == 'F')
		check_colors(line, 'F', &(g_map->floor));
	else
		return (-1);
	printf ("C %d %d %d\n", g_map->ceiling.r, g_map->ceiling.g, g_map->ceiling.b);
	printf ("F %d %d %d\n", g_map->floor.r, g_map->floor.g, g_map->floor.b);
	return (0);
}
