#include "parser.h"

int	parse(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
		write_err_and_exit("No map");
	else if (argc > 2)
		write_err_and_exit("Too many args");
	fd = open(argv[1], O_WRONLY);
	if (!fd)
		write_err_and_exit("Map not found");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3 - 1, ".cub", 5))
		write_err_and_exit("File is not .cub");
	
	return (0);
}