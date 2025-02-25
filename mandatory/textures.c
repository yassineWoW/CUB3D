#include "cub3d.h"

unsigned int    get_textures_pixel(t_image *textures, int x, int y)
{
    char *pixel;

    if (x < 0 || y < 0 || x >= textures->width || y >= textures->height)
        return (0);
    pixel = textures->addr + (y * textures->line_length + x * (textures->bpp / 8));

    return *(unsigned int*)pixel;
}

void draw_textured_strip(t_mlxing * mlx, int x, int start_y, int end_y, t_draw_params params)
{
    int     y = start_y;
    double  step = params.texture->height / params.wall_height;
    double  tex_pos = (start_y - WINDOW_HEIGHT/ 2 + params.wall_height / 2) * step;
    int     i = 0;
    int tex_y;
    unsigned int    color;

    while (i < start_y)
    {
        my_pixel_put(x, i, mlx->image, mlx->map->ceiling_color);
        i++;
    }

    while (y < end_y && y < WINDOW_HEIGHT)
    {
        if (y >= 0)
        {
            tex_y = (int)tex_pos & (params.texture->height - 1);
            color = get_textures_pixel(params.texture, params.tex_x, tex_y);
            my_pixel_put(x, y, mlx->image, color);
        }
        tex_pos +=  step;
        y++;
    }

    i = end_y;
    while (i < WINDOW_HEIGHT)
    {
        my_pixel_put(x, i, mlx->image, mlx->map->floor_color);
        i++;
    }
}

void cleanup_textures(t_mlxing *mlx)
{
    for (int i = 0; i < 4; i++)
    {
        if (mlx->map->textures[i])
        {
            if (mlx->map->textures[i]->image)
            {
                if (mlx->map->textures[i]->image->img)
                    mlx_destroy_image(mlx->mlx_connect, 
                        mlx->map->textures[i]->image->img);
                free(mlx->map->textures[i]->image);
            }
            free(mlx->map->textures[i]->name);
            free(mlx->map->textures[i]);
        }
    }
}


int init_textures(t_mlxing *mlx)
{
    int i = 0;
    int width=0, height=0;

    // perror("init_textures");

    while (i < 4)
    {
        mlx->map->textures[i]->image->img = mlx_xpm_file_to_image(mlx->mlx_connect,
            mlx->map->textures[i]->name, &width, &height);
        
        if (!mlx->map->textures[i]->image->img)
        {
            printf("Error loading texture : %s\n", mlx->map->textures[i]->name);
            return (0);
        }

        // (void)mlx;
        // (void)width;
        // (void)height;

        mlx->map->textures[i]->image->width = width;
        mlx->map->textures[i]->image->height = height;
        mlx->map->textures[i]->image->addr = mlx_get_data_addr(
            mlx->map->textures[i]->image->img,
            &mlx->map->textures[i]->image->bpp,
            &mlx->map->textures[i]->image->line_length,
            &mlx->map->textures[i]->image->endian);
        i++;
    }
    return (1);
}
