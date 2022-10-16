#include "../cube3d.h"

void	free_map(t_parsed_map *g_map)
{
	int	j;

	j = -1;
	while (++j < g_map->size.y)
		free(g_map->map[j]);
	free(g_map->map);
}

// void	free_textures(t_parsed_map *g_map)
// {
// 	free(g_map->texture.n);
// 	free(g_map->texture.s);
// 	free(g_map->texture.w);
// 	free(g_map->texture.e);
// }
