#include "cub3d_bonus.h"

int check_textures_syntax(char *str)
{
    // EA+space+word+/0;
    // perror("here 4");
    if (!str)
        return (0);
    if (str[2] != ' ')
        return (0);
    int i = 3;
    while (str[i] && str[i] != ' ')
        i++;
    if (str[i] != '\0')
        return (0);
    return (1);
}

int parse_textures(char *str, t_map *map)
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

int check_colors_syntax(char *str)
{
    // F 220,100,0
    if (str[1] != ' ')
        return (0);

    int i = 2;
    short isnumberfound = 0;
    short iscommafound = 0;
    while (str[i])
    {
        // printf("%c\n", str[i]);
        if (str[i] != ',' && !(str[i] >= '0' && str[i] <= '9')
             && !(str[i] == '\n' && str[i+1]=='\0'))
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


int convert_rgb_toint(t_colors rgb)
{
    return (rgb.r)|(rgb.g<<8)|rgb.b;
}

int    fill_rgb(char **s, t_colors *color)
{
    int num[3];

    if (!s[0] || !s[1] || !s[2])
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

int set_colorsvalue(char *str, t_map *map)
{
    char **s;
    t_colors color;

    

    // str[strlen(str) - 1] = '\0';
    s = ft_split(str + 2, ',');
    if (!fill_rgb(s, &color))
    {   perror ("yes here 1\n");
        return (0);
    }
        
    if (!strncmp(str, "F", 1))
    {
        if (map->floor_color != -1)
        {
            perror ("yes here 2\n");
             return (0);
        }
           
        map->floor_color = convert_rgb_toint(color);
    }
    else if (!strncmp(str, "C", 1))
    {
        if (map->ceiling_color != -1)
        {   
            perror ("yes here 3\n");
             return (0);
        }
           
        map->ceiling_color = convert_rgb_toint(color);
    }
    return (1);
}

int parse_colors(char *str, t_map *map)
{
    if (!str)
        return (0);
    if (!check_colors_syntax(str))
        return (0); 
    if (!set_colorsvalue(str, map))
        return (0);
        
    // printf ("C : %d,%d,%d\n", game->C.r, game->C.g, game->C.b);
    // printf ("F : %d,%d,%d\n", game->F.r, game->F.g, game->F.b);
    return (1);
}

int is_map_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] == '0' || str[i] == '1') || 
				(str[i] == 'S' || str[i] == 'N' || str[i] == 'W' || str[i] == 'E') ||
				(str[i] == 'D' || str[i] == 'd')))
		{
		    return (0);
		}
		i++;
	}
	return (1);
}

void    free_db_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free (arr[i]);
        i++;
    }
    // free (arr[i]);
    arr = NULL;
}

int copy_old_lines(t_map *map, char *str)
{
    char  **tmp;
    int i = 0;

    if (!str || !map)
        return (0);
    tmp = malloc ((map->n_rows + 2) * sizeof(char *));
    while (map->grid[i])
    {
        tmp[i] = map->grid[i];
        i++;
    }
    tmp[i] =  ft_strdup(str);
    tmp[i + 1] = NULL;
    free (map->grid);
    map->grid = tmp;
    return (1);
}

int parse_map(char *str, t_map *map)
{
    copy_old_lines(map, str); 
    map->n_rows++;
    return (1);
}

int is_valid(char *str)
{
    int i;

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

int parseline(char *str, t_map *map)
{   
    if (!str)
        return (0);
    if (!strncmp(str, "\n", 1))
        return (1);
    str = ft_strtrim(str, "\n");
    if (!strncmp(str, "NO", 2) || !strncmp(str, "SO", 2) || 
        !strncmp(str, "EA", 2) || !strncmp(str, "WE", 2))
    {
        return (parse_textures(str, map));
    }
    else if (!strncmp(str, "F", 1) || !strncmp(str, "C", 1))
        return (parse_colors(str, map));
    else if (is_map_line(str))
        return (parse_map(str, map));
    else if (!is_valid(str))
        return (0);
    return (0);
}
void	init_game(t_mlxing *mlx)
{
    mlx->map->player->player_direction = '\0';
    mlx->map->grid = malloc(sizeof(char**));
    if (!mlx->map->grid)
    {
        free(mlx->map->player);
        free(mlx->map);
        return ;
    }
    mlx->map->grid[0] = NULL;
    mlx->map->n_rows = 0;

    short i = 0;
    while (i < 4)
    {
        mlx->map->textures[i] = malloc(sizeof(t_textures));
        if (!mlx->map->textures[i])
        {
            // Cleanup previously allocated textures
            while (--i >= 0)
            {
                free(mlx->map->textures[i]->image);
                free(mlx->map->textures[i]);
            }
            free(mlx->map->grid);
            free(mlx->map->player);
            free(mlx->map);
            return ;
        }
        mlx->map->textures[i]->image = malloc(sizeof(t_image));
        if (!mlx->map->textures[i]->image)
        {
            free(mlx->map->textures[i]);
            // Cleanup previously allocated textures
            while (--i >= 0)
            {
                free(mlx->map->textures[i]->image);
                free(mlx->map->textures[i]);
            }
            free(mlx->map->grid);
            free(mlx->map->player);
            free(mlx->map);
            return ;
        }
        // Initialize all fields
        mlx->map->textures[i]->name = NULL;
        mlx->map->textures[i]->image->img = NULL;
        mlx->map->textures[i]->image->addr = NULL;
        i++;
    }
    mlx->map->ceiling_color = -1;
    mlx->map->floor_color = -1;
    mlx->map->cell_height = -1;
    mlx->map->cell_width = -1;
    mlx->map->map_height = -1;
    mlx->map->map_width = -1;
    return ;
}

int is_one_player(t_map *map)
{
    int players_count = 0;
    int i = 0, j = 0;
    while (i < map->n_rows)
    {
        // printf("%s\n", game->map->map[i]);
        j = 0;
        while (map->grid[i][j])
        {
            if (map->grid[i][j] == 'S' || map->grid[i][j] == 'N' ||
                 map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
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
        // printf("here 1\n");
        return (0);
    }
        
    return (1);
}

int is_map_closed(t_map *map)
{
    int i = 0;
    int j = 0;

    while (map->grid[i])
    {
        j = strlen(map->grid[i]) - 1;
        if (map->grid[i][0] != '1' || map->grid[i][j] != '1')
            return (0);
        i++;
    }
    return (1);
}

int is_opened(char *str)
{
    int fd;


    fd = open(str, O_RDONLY, 0777);
    if (fd == -1)
        return (0);
    else
        close (fd);
    return(1);
}

int is_textures_accesible(t_map  *map)
{
    printf("%s\n", map->textures[0]->name);
	printf("%s\n", map->textures[1]->name);
	printf("%s\n", map->textures[2]->name);
	printf("%s\n", map->textures[3]->name);
	if (!map->textures[0]->name || !map->textures[1]->name || !map->textures[2]->name 
            || !map->textures[3]->name)
                return (0);
        
    
    short i = 0;
    while (i < 4)
    {
        if (!is_opened(map->textures[i]->name))
            return (0);
        i++;
    }
    return (1);
}

int check_colors(t_map *map)
{
    if (map->ceiling_color == -1 || map->floor_color == -1)
        return (0);
    return (1);
}

int get_max_width(t_map *map)
{
	int	i;
	int	length;
	int	max_width;

	i = 0;
	max_width = 0;
	if (!map->grid[0])
		return (0);
	while (map->grid[i])
	{
		length = ft_strlen(map->grid[i]);
		if (length > max_width)
			max_width = length;
		i++;
	}
	map->map_width = max_width;
	return (max_width);
}

char **pad_map_grid(char **grid, int map_height, int map_width)
{
	char	**padded_grid;
	int		x;
	int		y;
	int		line_width;

	x = 0;
	y = 0;
	padded_grid = malloc(map_height * sizeof(char *));
	if (!padded_grid)
	{
		perror("Failed to allocate memory for padded grid");
		exit(EXIT_FAILURE);
	}
	while (y < map_height)
	{
		padded_grid[y] = malloc((map_width + 1) * sizeof(char));
		if (!padded_grid[y])
		{
			perror("Failed to allocate memory for padded grid line");
			exit(EXIT_FAILURE);
		}
		line_width = ft_strlen(grid[y]);
		ft_strcpy(padded_grid[y], grid[y]);
		x = line_width;
		while (x < map_width)
		{
			padded_grid[y][x] = '1';
			x++;
		}
		padded_grid[y][map_width] = '\0'; // Null-terminate the line
		y++;
	}
	return (padded_grid);
}

int	is_door_valid(t_map *map, int y, int x)
{
	if (y == 0 || y == map->map_height - 1
		|| x == 0 || x == map->map_width - 1)
		return (0);
	if (map->grid[y - 1][x] != '1' || map->grid[y + 1][x] != '1'
		|| map->grid[y][x - 1] != '1' || map->grid[y][x + 1] != '1')
		return (0);
	return (1);
}

void free_grid(char **grid, int height)
{
    if (!grid)
        return;

    for (int y = 0; y < height; y++)
    {
        if (grid[y])
            free(grid[y]);
    }
    free(grid);
}

void	count_and_store_doors(t_map *map)
{
	int	y;
	int	x;
	int	door_index;

	y = -1;
	door_index = 0;
	map->door_count = 0;
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_width)
		{
			if (map->grid[y][x] == 'D' || map->grid[y][x] == 'd')
				map->door_count++;
		}
	}
	map->doors = malloc(map->door_count * sizeof(t_door));
	if (!map->doors)
		exit_with_error("Failed to allocate memory for doors");
	y = -1;
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_width)
		{
			if (map->grid[y][x] == 'D' || map->grid[y][x] == 'd')
			{
				if (!is_door_valid(map, y, x))
					exit_with_error("Invalid door placement");
				map->doors[door_index].x = x;
				map->doors[door_index].y = y;
				map->doors[door_index].is_open = (map->grid[y][x] == 'd');
				door_index++;
			}
		}
	}
}

int	check_data(t_map *map)
{
	char	**padded;

	if (!is_one_player(map) || !is_map_closed(map)
		|| !is_textures_accesible(map) || !check_colors(map))
		return (0);
	map->map_height = map->n_rows;
	map->map_width = get_max_width(map);
	padded = pad_map_grid(map->grid, map->map_height, map->map_width);
	free_grid(map->grid, map->map_height);
	map->grid = padded;
	count_and_store_doors(map);
	return (1);
}

void	parse_cub(char *file, t_mlxing *mlx)
{
    char *str;
    int fd;
   
    fd = open(file, O_RDONLY, 0777);
    if (fd == -1)
		return;
	init_game(mlx);
    while ((str = get_next_line(fd)) != NULL)
    {
        if (!parseline(str, mlx->map))
        {
            free (str);
             free_parsing(mlx->map); 
            return ;
        }
        free (str);
    }
    if (!check_data(mlx->map))
    {
        perror ("yes error in function check data\n");
        free_parsing(mlx->map);
        return ;
    }
    return ;
}

void	exit_with_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	set_player_angle(t_player *player, char direction)
{
	if (direction == 'N')
		player->angle = -M_PI / 2;
	else if (direction == 'S')
		player->angle = M_PI / 2;
	else if (direction == 'W')
		player->angle = M_PI;
	else if (direction == 'E')
		player->angle = 0.0;
}

void	init_player(t_mlxing *mlx)
{
	int	y;
	int	x;

	if (!mlx->map->player)
		exit_with_error("Failed to allocate memory for player");
	y = -1;
	while (++y < mlx->map->map_height)
	{
		x = -1;
		while (++x < mlx->map->map_width)
		{
			if (mlx->map->grid[y][x] == 'N' || mlx->map->grid[y][x] == 'S'
				|| mlx->map->grid[y][x] == 'W' || mlx->map->grid[y][x] == 'E')
			{
				if (mlx->map->grid[y][x] == 'D' || mlx->map->grid[y][x] == 'd')
					exit_with_error("Player cannot spawn on a door");
				mlx->map->player->x = x + 0.5;
				mlx->map->player->y = y + 0.5;
				set_player_angle(mlx->map->player, mlx->map->grid[y][x]);
				mlx->map->grid[y][x] = '0';
				return ;
			}
		}
	}
	exit_with_error("No player starting position (N, S, W, E) found in the map");
}