/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 03:20:11 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/18 22:30:59 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	parsemapline(t_map *map, char *str)
{
	if (map->_ismapfound == 0)
		map->_isnewlinefound = 0;
	else
	{
		if (map->_isnewlinefound == 1)
			return (0);
	}
	map->_ismapfound = 1;
	if (!all_element_founded(map))
		return (0);
	return (parse_map(str, map));
}

int	parseline(char *str, t_map *map)
{
	if (!str)
		return (0);
	if (!strncmp(str, "\n", 1))
	{
		map->_isnewlinefound = 1;
		return (1);
	}
	str = ft_strtrim(str, "\n ");
	if (!strncmp(str, "NO", 2) || !strncmp(str, "SO", 2) || !strncmp(str, "EA",
			2) || !strncmp(str, "WE", 2))
	{
		return (parse_textures(str, map));
	}
	else if (!strncmp(str, "F", 1) || !strncmp(str, "C", 1))
		return (parse_colors(str, map));
	else if (is_map_line(str))
	{
		return (parsemapline(map, str));
	}
	return (0);
}

void	init_file(int fd, t_mlxing *mlx)
{
	if (fd == -1)
	{
		ft_putstr_fd("wrong .cub file\n", 2);
		cleanup_animation(mlx, mlx->shoot_animation);
		ft_malloc(0, 1);
		exit(0);
	}
	init_game(mlx);
	if (!mlx->map->grid)
	{
		free_parsing(mlx, 1);
	}
}

void	parse_cub(char *file, t_mlxing *mlx)
{
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY, 0777);
	init_file(fd, mlx);
	str = get_next_line(fd);
	while (str)
	{
		if (!parseline(str, mlx->map))
		{
			free(str);
			get_next_line(-3);
			free_parsing(mlx, 1);
			return ;
		}
		free(str);
		str = get_next_line(fd);
	}
	if (!check_data(mlx->map, mlx))
	{
		free_parsing(mlx, 1);
	}
}
