/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:50:52 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 19:50:53 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h"
#include "cub3d.h"

void	free_dbl_arr(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_tools(t_mlxing *mlx, int flag)
{
	if (mlx->image)
	{
		free(mlx->image);
	}
	if (mlx->map->player)
		free(mlx->map->player);
	if (mlx->map)
		free(mlx->map);
	if (mlx->keys)
		free(mlx->keys);
	if (mlx->rays)
		free(mlx->rays);
	if (mlx)
		free(mlx);
	if (flag)
		ft_putstr_fd("parsing failed\n", 2);
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
			{
				if (mlx->map->textures[i]->image->img)
					free(mlx->map->textures[i]->image->img);
				free(mlx->map->textures[i]->image);
			}
			free(mlx->map->textures[i]);
		}
		i++;
	}
	free_tools(mlx, flag);
	exit(EXIT_FAILURE);
}
