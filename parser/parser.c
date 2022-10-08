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
	// printf("t %d path %s str %s\n", t, path, str);
	t = open(path, O_RDONLY);
	printf("t %d path %s str %s\n", t, path, str);
	if (t > 0)
	{
		free(path);
		return (t);
	}
	else
		write_err_and_exit("Texture not found");
	return (0);
}

int	check_textures(int fd)
{
	check_path(get_next_line(fd), "NO ");
	check_path(get_next_line(fd), "SO ");
	check_path(get_next_line(fd), "WE ");
	check_path(get_next_line(fd), "EA ");

	return (0);
}

int	parse(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
		write_err_and_exit("No map");
	else if (argc > 2)
		write_err_and_exit("Too many args");
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		write_err_and_exit("Map not found");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3 - 1, ".cub", 5))
		write_err_and_exit("File is not .cub");
	check_textures(fd);
	return (0);
}