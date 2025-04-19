/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:09:17 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 02:12:55 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_dbl_arr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_parsing_of_exit(t_mlxing *mlx, int flag)
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
	ft_malloc(0, 1);
	if (flag)
		ft_putstr_fd("parsing failed\n", 2);
	exit(EXIT_SUCCESS);
}

void	free_img_animation_exit(t_mlxing *mlx, int flag)
{
	if (mlx->initial_img)
	{
		free(mlx->initial_img);
		mlx->initial_img = NULL;
	}
	if (mlx->shoot_animation != NULL)
	{
		free(mlx->shoot_animation);
		mlx->shoot_animation = NULL;
	}
	ft_malloc(0, 1);
	if (flag)
		ft_putstr_fd("parsing failed\n", 2);
	exit(EXIT_SUCCESS);
}

void	free_parsing(t_mlxing *mlx, int flag)
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
	free_img_animation_exit(mlx, flag);
}

void	free_animation_exit(t_mlxing *mlx, int flag)
{
	if (mlx->shoot_animation != NULL)
	{
		free(mlx->shoot_animation);
		mlx->shoot_animation = NULL;
	}
	ft_malloc(0, 1);
	if (flag)
		ft_putstr_fd("parsing failed\n", 2);
	exit(EXIT_SUCCESS);
}
