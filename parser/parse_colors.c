#include "../cube3d.h"

int skip_comma(char **str)
{
	while (is_space(**str))
		(*str)++;
	if (**str != ',')
		return (-1);
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
	return (-1);
}

int	check_ce_and_fl(char *line, t_parsed_map *g_map)
{
	check_colors(line, 'F', &(g_map->ceiling));
	// check_colors(line, "C ", g_map->floor);

	return (0);
}