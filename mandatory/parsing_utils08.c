/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils08.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:16:40 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:33:57 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_player_grid(t_mlxing *mlx)
{
	mlx->map->player->player_direction = '\0';
	mlx->map->grid = malloc(sizeof(char **));
	if (!mlx->map->grid)
	{
		free(mlx->map->player);
		free(mlx->map);
		return (0);
	}
	mlx->map->grid[0] = NULL;
	mlx->map->n_rows = 0;
	return (1);
}

void	init_value(t_mlxing *mlx)
{
	mlx->map->ceiling_color = -1;
	mlx->map->floor_color = -1;
	mlx->map->cell_height = -1;
	mlx->map->cell_width = -1;
	mlx->map->map_height = -1;
	mlx->map->map_width = -1;
	mlx->map->isceiling_color = 0;
	mlx->map->isfloor_color = 0;
	mlx->map->_ismapfound = 0;
	mlx->map->_isnewlinefound = 0;
}

void	free_old_textures(t_mlxing *mlx, int i)
{
	while (--i >= 0)
	{
		free(mlx->map->textures[i]);
	}
	free(mlx->map->grid);
	free(mlx->map->player);
	free(mlx->map);
	return ;
}

void	init_game(t_mlxing *mlx)
{
	short	i;

	if (!allocate_player_grid(mlx))
		return ;
	i = 0;
	while (i < 4)
	{
		mlx->map->textures[i] = malloc(sizeof(t_textures));
		if (!mlx->map->textures[i])
		{
			free_old_textures(mlx, i);
			return ;
		}
		mlx->map->textures[i]->image = malloc(sizeof(t_image));
		if (!mlx->map->textures[i]->image)
		{
			free_old_textures(mlx, i);
			return ;
		}
		mlx->map->textures[i]->name = NULL;
		mlx->map->textures[i]->image->img = NULL;
		mlx->map->textures[i]->image->addr = NULL;
		i++;
	}
	init_value(mlx);
}

int	count_word(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
