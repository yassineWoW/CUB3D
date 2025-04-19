/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:17:30 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/15 03:17:31 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_player_map(t_mlxing *mlx, char *file)
{
	parse_cub(file, mlx);
	init_player(mlx);
}

t_mlxing	*init_mlx_structure(void)
{
	t_mlxing	*mlx;

	mlx = NULL;
	mlx = ft_malloc(sizeof(t_mlxing), 0);
	mlx->map = ft_malloc(sizeof(t_map), 0);
	mlx->image = ft_malloc(sizeof(t_image), 0);
	mlx->map->player = ft_malloc(sizeof(t_player), 0);
	mlx->keys = ft_malloc(sizeof(t_keys), 0);
	if (init_shoot_anim(mlx))
		return (NULL);
	return (mlx);
}

static void	cleanup_mlx_structure(t_mlxing *mlx)
{
	if (mlx->keys)
		free(mlx->keys);
	if (mlx->map->player)
		free(mlx->map->player);
	if (mlx->image)
		free(mlx->image);
	if (mlx->map)
		free(mlx->map);
	if (mlx)
		free(mlx);
}

int	main(int ac, char **av)
{
	t_mlxing	*mlx;

	if (ac != 2)
	{
		perror("Usage: ./cub3D <path_to_map.cub>");
		return (1);
	}
	mlx = init_mlx_structure();
	if (!mlx)
	{
		perror("Failed to initialize mlx structure");
		return (1);
	}
	keyinit(mlx->keys);
	init_player_map(mlx, av[1]);
	if (!init_mlx(mlx))
	{
		exit_game(mlx, 0);
		return (0);
	}
	cleanup_mlx_structure(mlx);
	return (0);
}
