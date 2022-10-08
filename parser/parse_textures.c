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

#include "../cube3d.h"

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
//тут получаем пути картинок
int	check_path(char *str, char *dir)
{
	char	*path;
	int		t;

	if (ft_strlen(str) < 4 || ft_strncmp(str, dir, 3))
		write_err_and_exit("Wrong textures token");
	t = get_path_len(str + 3);
	if (!t)
		return (-1);
	path = (char *)malloc(sizeof(char) * (t + 1));
	ft_memmove(path, str + 3, t + 1);
	path[t] = '\0';
	t = open(path, O_RDONLY);
	printf("t %d path %s str %s\n", t, path, str);
	if (t > 0)
	{
		if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 5))
			write_err_and_exit("Texture is not .xpm");
		free(path);
		return (t);
	}
	else
		write_err_and_exit("Texture not found");
	return (0);
}

int	check_textures(int fd)
{
	g_map.texture.n = check_path(get_next_line(fd), "NO ");
	g_map.texture.s = check_path(get_next_line(fd), "SO ");
	g_map.texture.w = check_path(get_next_line(fd), "WE ");
	g_map.texture.e = check_path(get_next_line(fd), "EA ");

	return (0);
}
