/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:05:17 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:41:16 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	i;
	int	width;
	int	height;

	i = 0;
	width = 0;
	height = 0;
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

int	parse_textures(char *str, t_map *map)
{
	if (!str)
		return (0);
	if (!check_textures_syntax(str))
		return (0);
	if (!strncmp(str, "NO", 2) && !map->textures[0]->name)
		map->textures[0]->name = ft_strdup(str + 3);
	else if (!strncmp(str, "SO", 2) && !map->textures[1]->name)
		map->textures[1]->name = ft_strdup(str + 3);
	else if (!strncmp(str, "EA", 2) && !map->textures[2]->name)
		map->textures[2]->name = ft_strdup(str + 3);
	else if (!strncmp(str, "WE", 2) && !map->textures[3]->name)
		map->textures[3]->name = ft_strdup(str + 3);
	else
		return (0);
	return (1);
}
