#include "parser.h"

int	parse(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
		write_err_and_exit("No map(");
	else if (argc > 2)
		write_err_and_exit("Too many args");
	fd = open(argv[1], O_WRONLY);
	return (0);
}