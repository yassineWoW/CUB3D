/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:29:10 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 23:28:09 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map_line(t_map *map, char *str)
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
		return (parse_map_line(map, str));
	}
	return (0);
}

void	parse_cub(char *file, t_mlxing *mlx)
{
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("wrong .cub file\n");
		exit(EXIT_FAILURE);
	}
	init_game(mlx);
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
	if (!check_data(mlx->map))
		free_parsing(mlx, 1);
}
