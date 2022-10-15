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
			g_map->size.x = len - 1;
		g_map->size.y++;
		free(line);
		line = get_next_line(fd);
	}
	g_map->size.y++;
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
	g_map->map = (int **)malloc(sizeof(int *) * (g_map->size.y + 2));
	if (!g_map->map)
		write_err_and_exit("Malloc error");
	while (j < g_map->size.y)
	{
		g_map->map[j] = (int *)malloc(sizeof(int) * (g_map->size.x + 1));
		if (!g_map->map)
			write_err_and_exit("Malloc error");
		j++;
	}
}

// есть ли разрешенный символ (0, 1, ' ', N, S, E, W)
int	is_allowed(int c)
{
	if (c == '1')
		return(1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (c);
	else if (c == '0')
		return (0);
	return (-1);
}

int	allow(int c)
{
	if (c == 1)
		return(1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 0)
		return (0);
	return (-1);
}

void	check_holes(t_parsed_map *g_map, int i, int j)
{
	if ((g_map->map[j][i] == ' ' &&
			allow(g_map->map[j][i - 1]) == 0 && i < g_map->size.x)
					|| (i == g_map->size.x &&
							allow(g_map->map[j][i - 1]) == 0))
		write_err_and_exit("hole in wall");
	if (i == g_map->size.x && allow(g_map->map[j][i - 1]) == 0)
		write_err_and_exit("hole in wall");
}

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
				break;
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
	// if (j == g_map->size.y)
	// 	return ;
	if ((j == g_map->size.y && allow(g_map->map[j - 1][i]) == 0))
		write_err_and_exit("hole in wall");
	if (j == g_map->size.y)
		return ;
	if ((g_map->map[j][i] == ' ' &&
			allow(g_map->map[j - 1][i]) == 0 && j < g_map->size.y))
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
				break;
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
	// check columns
	return (0);
}

int	parse_map(int fd, t_parsed_map *g_map)
{
	char	*line;
	int		i;
	int		j;

	create_arr(g_map);
	j = 0;
	line = get_next_line(fd);
	while (line && j < g_map->size.y)
	{
		i = 0;
		while (line[i] && is_allowed(line[i]) != -1)
		{
			g_map->map[j][i] = is_allowed(line[i]);
			i++;
		}
		if (i < g_map->size.x - 1 && line[i] != '\n' && line[i] != '\0')
			write_err_and_exit("Wrong symbols in map");
		while (i < g_map->size.x)
		{
			g_map->map[j][i] = ' ';
			i++;
		}
		free(line);
		line = get_next_line(fd);
		j++;
	}
	check_map(g_map);
	return (0);
}