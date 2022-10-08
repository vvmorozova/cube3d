#include "../cube3d.h"

int write_err_and_exit(char *err)
{
    printf("Error\n%s\n", err);
    exit(0);
}

int is_space(char c)
{
    if (c == ' ' || c == '\n'
            || c == '\t' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    else 
        return (0);
}