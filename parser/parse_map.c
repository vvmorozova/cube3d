/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:04:38 by eward             #+#    #+#             */
/*   Updated: 2022/10/09 18:04:39 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	count_h_w(int fd, int how_many_to_skip, char *filename, t_parsed_map *g_map)
{
	char	*line;
	int		len;

	g_map->size.x = 0;
	g_map->size.y = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > g_map->size.x)
			g_map->size.x = len;
		g_map->size.y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	while (how_many_to_skip)
	{
		get_next_line(fd);
		how_many_to_skip--;
	}
	return (fd);
}

void	create_arr(t_parsed_map *g_map)
{
	int	j;

	j = 0;
	g_map->map = (int **)malloc(sizeof(char *) * (g_map->size.y + 2));
	if (!g_map->map)
		write_err_and_exit("Malloc error");
	while (j < g_map->size.y)
	{
		g_map->map[j] = (int *)malloc(sizeof(char) * (g_map->size.x + 2));
		if (!g_map->map)
			write_err_and_exit("Malloc error");
		ft_memset(g_map->map[j], ' ', g_map->size.x);
		j++;
	}
}

int	parse_map(int fd, t_parsed_map *g_map)
{
	char	*line;
	int		i;
	int		j;

	create_arr(g_map);
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == '0' || line[i] == '1'))
		{
			g_map->map[i][j] = line[i] - '0';
			i++;
		}
		g_map->map[i][j] = '\0';
		free(line);
		line = get_next_line(fd);
		j++;
	}
	g_map->map[i] = NULL;
	return (0);
}