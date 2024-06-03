/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:48:14 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/17 17:54:10 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*get_point_list(t_map *map)
{
	t_point	*point_list;
	float	bottom_left_x;
	float	bottom_left_y;
	int		i;

	point_list = (t_point *)malloc(map->width * map->height * sizeof(t_point));
	if (!point_list)
		return (NULL);
	bottom_left_x = -((float)map->width * 0.5 - 0.5) * map->dimensions.x;
	bottom_left_y = -((float)map->height * 0.5 - 0.5) * map->dimensions.y;
	i = 0;
	while (i < map->width * map->height)
	{
		point_list[i] = (t_point){bottom_left_x + (float)(i % map->width) \
			* map->dimensions.x, bottom_left_y + (float)(i / map->width) * \
			map->dimensions.y, (float)map->map[i] * map->dimensions.z};
		i++;
	}
	return (point_list);
}

static int	add_lines(t_line_index *line, int i, int j, t_map *map)
{
	static const int	delta[2][2] = {{1, 0}, {0, 1}};
	int					count;
	int					k;

	k = -1;
	count = 0;
	while (++k < 2)
	{
		if (i + delta[k][0] < 0 || i + delta[k][0] >= map->height || \
			j + delta[k][1] < 0 || j + delta[k][1] >= map->width)
			continue ;
		(line + count)->il1 = (i + delta[k][0]) * map->width + j + delta[k][1];
		(line + count)->il2 = i * map->width + j;
		count++;
	}
	return (count);
}

int	fetch_lines(t_map *map)
{
	int			lli;
	int			i;
	int			j;

	map->lines = ft_calloc(map->line_count, sizeof(t_line_index));
	if (!map->lines)
		return (0);
	i = -1;
	lli = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			lli += add_lines(map->lines + lli, i, j, map);
	}
	return (1);
}

t_point	calculate_map_dimensions(t_map *map)
{
	int	max;

	max = ft_max(map->width, map->height);
	return ((t_point){
		.x = DEFAULT_BOX_X / max,
		.y = DEFAULT_BOX_Y / max,
		.z = DEFAULT_BOX_Z / (float)ft_max((map->top - map->bottom), 1)
	});
}
