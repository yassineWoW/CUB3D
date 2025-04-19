/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:24:08 by ainouni           #+#    #+#             */
/*   Updated: 2025/04/17 22:47:27 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	validate_colors_syntax(char *str)
{
	int		i;
	short	isnumberfound;
	short	iscommafound;

	i = 0;
	isnumberfound = 0;
	iscommafound = 0;
	while (str[i])
	{
		if (str[i] != ',' && !(str[i] >= '0' && str[i] <= '9')
			&& !(str[i] == '\n' && str[i + 1] == '\0') && !(str[i] == ' '))
			return (0);
		if (str[i] == ',')
		{
			if (!isnumberfound)
				return (0);
			iscommafound = 1;
			isnumberfound = 0;
		}
		if ((str[i] >= '0' && str[i] <= '9'))
			isnumberfound = 1;
		i++;
	}
	(void)iscommafound;
	return (1);
}

int	is_just_nb_and_space(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && !(*s == ' '))
			return (0);
		s++;
	}
	return (1);
}

int	check_double_nb(char **s)
{
	int (i), (j), (isnbfound), (nbcount);
	i = 0;
	while (s[i])
	{
		j = 0;
		isnbfound = 0;
		nbcount = 0;
		while (s[i][j])
		{
			if (count_nb(s[i][j], &isnbfound))
				nbcount++;
			j++;
		}
		if (nbcount > 1)
			return (0);
		i++;
	}
	return (1);
}

int	fill_rgb(char **s, t_colors *color)
{
	int	num[3];

	if (!s[0] || !s[1] || !s[2])
		return (0);
	if (!is_just_nb_and_space(s[0]) || !is_just_nb_and_space(s[1])
		|| !is_just_nb_and_space(s[2]))
		return (0);
	if (!check_double_nb(s))
		return (0);
	num[0] = ft_atoi(s[0]);
	num[1] = ft_atoi(s[1]);
	num[2] = ft_atoi(s[2]);
	if ((num[0] > 255 || num[0] < 0) || (num[1] > 255 || num[1] < 0)
		|| num[2] > 255 || num[2] < 0)
		return (0);
	color->r = num[0];
	color->g = num[1];
	color->b = num[2];
	free_dbl_arr(s);
	return (1);
}
