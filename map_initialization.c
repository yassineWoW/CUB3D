#include "cub3d.h"

static void	parse_map(char *line, t_map *map, int i)
{
	int 	len;
	int 	j;
	int 	k;

	k = 0;
	j = 0;
	len = ft_strlen(line);
	map->map_width = len;
	map->grid[i] = malloc(sizeof(char) * (map->map_width + 1));
	while (j < map->map_width)
	{
		map->grid[i][j] = line[k];
		j++;
		k++;
	}
	map->grid[i][j] = '\0';
}

static int	calculate_height(char *filename)
{
	int		file;
	char	*line;
	int		height;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (0);
	height = 0;
	line = get_next_line(file);
	while (line)
	{
		if (line[0] == '1')
			height++;
		free(line);
		line = NULL;
		line = get_next_line(file);
	}
	close(file);
	return (height);
}

static int	parse_cub_file(char *filename, t_map *map)
{
	char	*line;
	int		file;
	int		i;
	
	map->map_height = calculate_height(filename);
	map->grid = malloc(sizeof(char **) * (map->map_height + 1));
	map->grid[(int)map->map_height] = NULL;
	i = 0;
	file = open(filename, O_RDONLY);
	if (file < 0)
		return (0);
	line = get_next_line(file);
	while (line)
	{
		if (line[0] == '1')
			parse_map(line, map, i);
		//if (line[0] == 'R')
		//	parse_resolution(line, map);
		//else if (line[0] == 'F')
		//	parse_floor_color(line, map);
		//else if (line[0] == 'C')
		//	parse_ceiling_color(line, map);
		//else if (line[0] == 'N' && line[1] == 'O')
		//	parse_north_texture(line, map);
		//else if (line[0] == 'S' && line[1] == 'O')
		//	parse_south_texture(line, map);
		//else if (line[0] == 'W' && line[1] == 'E')
		//	parse_west_texture(line, map);
		//else if (line[0] == 'E' && line[1] == 'A')
		//	parse_east_texture(line, map);
		//else if (line[0] == 'S')
		//	parse_sprite_texture(line, map);
		free(line);
		line = NULL;
		line  = get_next_line(file);
		i++;
	}
	if (line)
		free(line);
	return (file);
}

void	init_map_details(t_mlxing *mlx)
{
	mlx->map->ceiling_color = CYAN;
	mlx->map->floor_color = WHITE;
	parse_cub_file("map.cub", mlx->map);
}
