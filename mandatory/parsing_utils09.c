/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils09.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:24:22 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:42:21 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**pad_map_grid(char **grid, int map_height, int map_width)
{
	char	**padded_grid;
	int		x;
	int		y;
	int		line_width;

	x = 0;
	y = 0;
	padded_grid = malloc((map_height + 1) * sizeof(char *));
	if (!padded_grid)
		exit(EXIT_FAILURE);
	while (y < map_height)
	{
		padded_grid[y] = malloc((map_width + 1) * sizeof(char));
		if (!padded_grid[y])
			exit(EXIT_FAILURE);
		line_width = ft_strlen(grid[y]);
		ft_strcpy(padded_grid[y], grid[y]);
		x = line_width;
		while (x++ < map_width)
			padded_grid[y][x] = '1';
		padded_grid[y][map_width] = '\0';
		y++;
	}
	padded_grid[y] = NULL;
	return (padded_grid);
}

int	count_nb(char c, int *isnbfound)
{
	if (ft_isdigit(c))
	{
		if (!*isnbfound)
		{
			*isnbfound = 1;
			return (1);
		}
	}
	else
		*isnbfound = 0;
	return (0);
}

int	check_gap(t_map *map, int i, int j)
{
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
		|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' '
		|| map->grid[i - 1][j] == '\0' || map->grid[i + 1][j] == '\0'
		|| map->grid[i][j - 1] == '\0' || map->grid[i][j + 1] == '\0')
		return (0);
	return (1);
}
