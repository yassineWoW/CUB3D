/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils05.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:47:49 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 20:49:14 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] == '0' || str[i] == '1') || (str[i] == 'S'
					|| str[i] == 'N' || str[i] == 'W' || str[i] == 'E')
				|| (str[i] == 32)))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*remove_char(char *s, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(s);
	while (s[i])
	{
		if (s[i] != c)
		{
			s[j] = tmp[i];
			j++;
		}
		i++;
	}
	free(tmp);
	return (s);
}

int	parse_map(char *str, t_map *map)
{
	if (!check_map_syntax(str))
	{
		return (0);
	}
	copy_old_lines(map, str);
	map->n_rows++;
	return (1);
}

int	is_valid(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int	all_element_founded(t_map *map)
{
	return (map->ceiling_color != -1 && map->floor_color != -1
		&& map->textures[0]->name != NULL && map->textures[1]->name != NULL
		&& map->textures[2]->name != NULL && map->textures[3]->name != NULL);
}
