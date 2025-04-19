/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils04.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:33:30 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:58:48 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_one_player(t_map *map)
{
	int (players_count), (i), (j);
	i = 0;
	j = 0;
	players_count = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'S' || map->grid[i][j] == 'N'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				players_count++;
				map->player->player_direction = map->grid[i][j];
			}
			j++;
		}
		i++;
	}
	if (players_count == 0 || players_count > 1)
	{
		return (0);
	}
	return (1);
}

int	check_top_bottom(t_map *map)
{
	int	i;
	int	j;

	i = strlen(map->grid[0]);
	j = 0;
	while (j < i)
	{
		if (map->grid[0][j] != '1')
			return (0);
		j++;
	}
	i = strlen(map->grid[map->n_rows - 1]);
	j = 0;
	while (j < i)
	{
		if (map->grid[map->n_rows - 1][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	check_gap(t_map *map, int i, int j)
{
	if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
		|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' '
		|| map->grid[i - 1][j] == '\0' || map->grid[i
		+ 1][j] == '\0' || map->grid[i][j - 1] == '\0'
		|| map->grid[i][j + 1] == '\0')
		return (0);
	return (1);
}

int	check_edge(t_map *map)
{
	int (i), (row_len), (j);
	i = 0;
	row_len = 0;
	j = 0;
	while (i < map->n_rows - 1)
	{
		row_len = strlen(map->grid[i]);
		while (j < row_len - 1)
		{
			if (map->grid[i][j] == '0' || map->grid[i][j] == 'N'
				|| map->grid[i][j] == 'S' || map->grid[i][j] == 'E'
				|| map->grid[i][j] == 'W')
			{
				if (!check_gap(map, i, j))
					return (0);
			}
			else if (map->grid[i][j] != '1' && map->grid[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_closed(t_map *map)
{
	if (!map || !map->grid)
		return (0);
	if (!check_left_right(map))
		return (0);
	if (!check_top_bottom(map))
		return (0);
	if (!check_edge(map))
		return (0);
	return (1);
}
