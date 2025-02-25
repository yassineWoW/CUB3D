
#include "cub3d.h"
#include "../LIBFT/libft.h"


void   free_dbl_arr(char **str)
{
    int i;

    if (!str)
        return;
    i = 0;
    while (str[i])
    {
        free (str[i]);
        i++;
    }
    free (str);
	str = NULL;
}

void free_parsing(t_map *map)
{
	if (!map)
        return ;
    // free_dbl_arr(map->map);
    free_dbl_arr(map->grid);

    short i = 0;
    while (i < 4)
    {
        if (map->textures[i])
        {
            if (map->textures[i]->name)
                free(map->textures[i]->name);
            free(map->textures[i]);
        }
        i++;
    }
    // free (map->textures);
    free(map->player);
    free(map);
	map = NULL;
	ft_putstr_fd("parsing failed\n", 2);
	exit(EXIT_FAILURE);
    // free map;
    // free colors;
    // free textures;
    // free game;
}