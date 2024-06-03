/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_points.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 13:37:47 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/17 14:49:15 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_size(int fd, t_map *map)
{
	char	*line;

	map->height = 0;
	line = get_next_line(fd);
	map->width = ft_wordcount(line);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->line_count = (map->width * map->height * 2 - \
		map->width - map->height);
	return (1);
}

static void	handle_point(t_map *map, int map_index, char *input)
{
	map->map[map_index] = ft_atoi_base(input, 10);
	if (map->map[map_index] > map->top)
		map->top = map->map[map_index];
	if (map->map[map_index] < map->bottom)
		map->bottom = map->map[map_index];
	if (ft_strchr(input, ','))
		map->colors[map_index] = ft_atoi_base(ft_strchr(input, ',') + 3, 16);
	else
		map->colors[map_index] = 0xFFFFFF;
}

static int	load_map(int fd, t_map *map)
{
	char	**split;
	char	*line;
	int		index;
	int		map_index;

	map_index = 0;
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (free(line), 0);
		index = 0;
		while (split[index])
		{
			handle_point(map, map_index, split[index]);
			map_index++;
			index++;
		}
		ft_free_split(split);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

static int	set_map_defaults(t_map *map)
{
	map->top = INT_MIN;
	map->bottom = INT_MAX;
	map->x_rotation = DEFAULT_X_ROTATION;
	map->y_rotation = DEFAULT_Y_ROTATION;
	map->z_rotation = DEFAULT_Z_ROTATION;
	map->offset_x = 0;
	map->offset_y = 0;
	map->map = (int *)malloc(map->height * map->width * sizeof(int));
	if (!map->map)
		return (0);
	map->colors = (int *)malloc(map->height * map->width * sizeof(int));
	if (!map->colors)
		return (free(map->map), 0);
	return (1);
}

t_map	*fetch_map(char *filename)
{
	t_map	*map;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (close(fd), NULL);
	if (!get_size(fd, map) || map->width == 0 || map->height == 0)
		return (close(fd), free(map), NULL);
	close(fd);
	if (!set_map_defaults(map))
		return (free(map), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(map->map), free(map->colors), free(map), NULL);
	if (!load_map(fd, map))
		return (free(map->map), free(map->colors), close(fd), free(map), NULL);
	close(fd);
	if (!fetch_lines(map))
		return (free(map->map), free(map->colors), free(map), NULL);
	map->dimensions = \
		calculate_map_dimensions(map);
	return (map);
}
