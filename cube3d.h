#ifndef CUBE3D_H
#define CUBE3D_H

#include "parser/parser.h"
#include "utils/utils.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_map_size{
    int x;
    int y;
}   t_map_size;

typedef struct s_parsed_map{
    t_map_size  size;
    char        direction;
    char        **map;
}   t_parsed_map;

#endif