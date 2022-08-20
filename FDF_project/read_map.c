#include "fdf.h"

void	ft_atoi_point(t_mlx *map, char symbol, t_point *point)
{
	if (symbol >= '0' && symbol <= '9')
	{
		(*point).space_flag = 0;
		map->map[(*point).y][(*point).x] = map->map[(*point).y][(*point).x]
			* 10 + (symbol - '0');
	}
	else if (symbol == ' ' && !(*point).space_flag)
	{
		(*point).space_flag++;
		map->map[(*point).y][(*point).x] = map->map[(*point).y][(*point).x]
			* (*point).sign;
		(*point).sign = 1;
		if ((*point).x + 1 < map->map_width)
			(*point).x++;
	}
	else if (symbol == '\n')
	{
		(*point).space_flag = 0;
		map->map[(*point).y][(*point).x] = map->map[(*point).y][(*point).x]
			* (*point).sign;
		(*point).sign = 1;
		(*point).x = 0;
		if ((*point).y + 1 < map->map_height)
			(*point).y++;
	}
}

void	ft_determine_size_of_map(int fd, t_mlx *map)
{
	long	bwr;
	char	symbol;
	short	space_flag;

	bwr = 1;
	symbol = 0;
	space_flag = 0;
	while (bwr)
	{
		bwr = read(fd, &symbol, 1);
		if (map->map_height == 0 && symbol == ' ' && !space_flag)
		{
			map->map_width += 1;
			space_flag++;
		}
		else if ((symbol >= '0' && symbol <= '9') || symbol == '-')
			space_flag = 0;
		else if (symbol == '\n')
			map->map_height += 1;
	}
	map->map_width -= 1;
	map->map_height -= 1;
}

void	ft_create_flat_map(t_mlx *map)
{
	int	y;
	int	x;

	map->map = malloc(sizeof(int *) * (map->map_height + 1));
	if (!map->map)
		exit(0);
	y = 0;
	while (y < map->map_height)
	{
		map->map[y] = malloc(sizeof(int) * (map->map_width + 1));
		if (!map->map[y])
			exit(0);
		x = 0;
		while (x < map->map_width)
		{
			map->map[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	ft_add_height_to_map(int fd, t_mlx *map)
{
	long	bwr;
	char	symbol;
	t_point	point;

	bwr = 1;
	point.x = 0;
	point.y = 0;
	point.sign = 1;
	point.space_flag = 0;
	while (bwr)
	{
		bwr = read(fd, &symbol, 1);
		if (symbol == '-' && point.sign > 0)
		{
			point.space_flag = 0;
			point.sign = -1;
		}
		else
			ft_atoi_point(map, symbol, &point);
	}
}

void	ft_read_map(char *file, t_mlx *map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	ft_determine_size_of_map(fd, map);
	close(fd);
	ft_create_flat_map(map);
	fd = open(file, O_RDONLY);
	ft_add_height_to_map(fd, map);
	close(fd);
}
