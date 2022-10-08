/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:40:04 by eward             #+#    #+#             */
/*   Updated: 2022/10/08 19:40:06 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5))
		write_err_and_exit("File is not .cub");
	check_textures(fd);
	if (*get_next_line(fd))
		write_err_and_exit("Wrong file formatting");
	// check_colors(fd);
	// if (*get_next_line(fd))
	// 	write_err_and_exit("Wrong file formatting");
	// check_map(fd);
	close(fd);
	return (0);
}
