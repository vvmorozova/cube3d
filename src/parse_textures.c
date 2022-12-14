/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:40:14 by eward             #+#    #+#             */
/*   Updated: 2022/10/08 19:40:16 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_path_len(char *str)
{
	int	len;

	len = 0;
	while (is_space(*str))
		str++;
	if (!*str)
		return (-1);
	while (!is_space(*str) && *str)
	{
		str++;
		len++;
	}
	if (*str)
		return (len);
	while (is_space(*str))
		str++;
	if (!*str || *str == '\n')
		return (len);
	else
		return (-1);
}

int	check_texture_path(char *path, int t)
{
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 5))
	{
		free(path);
		write_err_and_exit("Texture is not .xpm");
	}
	return (t);
}

//тут получаем пути картинок
int	check_path(char *str, char *dir, char **txt_path)
{
	char	*path;
	int		t;

	if (ft_strlen(str) < 4 || ft_strncmp(str, dir, 3))
		return (-2);
	str += 2;
	while (is_space(*str))
		str++;
	t = get_path_len(str);
	if (!t)
		return (-2);
	path = (char *)malloc(sizeof(char) * (t + 1));
	if (!path)
		write_err_and_exit("Error while allocating memory");
	ft_memmove(path, str, t + 1);
	path[t] = '\0';
	*txt_path = path;
	t = open(path, O_RDONLY);
	if (t > 0)
		return (check_texture_path(path, t));
	else
		write_err_and_exit("Texture not found");
	free(path);
	return (-2);
}

int	check_textures(char *line, t_parsed_map *g_map)
{
	if (g_map->texture.n < 0 && !ft_strncmp(line, "NO ", 3))
		g_map->texture.n = check_path(line, "NO ", &(g_map->txts_path[0]));
	else if (g_map->texture.s < 0 && !ft_strncmp(line, "SO ", 3))
		g_map->texture.s = check_path(line, "SO ", &(g_map->txts_path[1]));
	else if (g_map->texture.w < 0 && !ft_strncmp(line, "WE ", 3))
		g_map->texture.w = check_path(line, "WE ", &(g_map->txts_path[2]));
	else if (g_map->texture.e < 0 && !ft_strncmp(line, "EA ", 3))
		g_map->texture.e = check_path(line, "EA ", &(g_map->txts_path[3]));
	else
		return (-1);
	return (0);
}
