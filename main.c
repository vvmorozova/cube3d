#include "cube3d.h"

// t_parsed_map	g_map;

int	main(int argc, char **argv)
{
	t_parsed_map	g_map;
	// ft_bzero(&g_map, sizeof(t_parsed_map));
	parse(argc, argv, &g_map);
	return (0);
}