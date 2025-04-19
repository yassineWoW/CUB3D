/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils03.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:12:04 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:49:32 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_parsing1(t_mlxing *mlx, int flag)
{
	short	i;

	i = 0;
	if (!mlx->map)
		return ;
	if (mlx->map->grid)
		free_dbl_arr(mlx->map->grid);
	while (i < 4)
	{
		if (mlx->map->textures[i])
		{
			if (mlx->map->textures[i]->name)
				free(mlx->map->textures[i]->name);
			if (mlx->map->textures[i]->image)
				free(mlx->map->textures[i]->image);
			free(mlx->map->textures[i]);
			mlx->map->textures[i] = NULL;
		}
		i++;
	}
	free_animation_exit(mlx, flag);
}

void	cleanup_textures(t_mlxing *mlx)
{
	int	i;

	i = 0;
	while (i < 4)
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
		i++;
	}
}

int	init_textures(t_mlxing *mlx)
{
	int (i), (width), (height);
	width = 0;
	height = 0;
	i = 0;
	while (i < 4)
	{
		mlx->map->textures[i]->image->img = mlx_xpm_file_to_image(
				mlx->mlx_connect, mlx->map->textures[i]->name,
				&width, &height);
		if (!mlx->map->textures[i]->image->img)
			return (0);
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

unsigned int	get_textures_pixel(t_image *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	check_textures_syntax(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[2] != ' ')
		return (0);
	i = 3;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
