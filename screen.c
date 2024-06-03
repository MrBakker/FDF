/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screen.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:39:29 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/22 14:16:16 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	interpolate_color(int c1, int c2, float i)
{
	int		red;
	int		green;
	int		blue;

	red = (c1 >> 16) + ((c2 >> 16) - (c1 >> 16)) * i;
	green = (c1 >> 8 & 0xFF) + ((c2 >> 8 & 0xFF) - (c1 >> 8 & 0xFF)) * i;
	blue = (c1 & 0xFF) + ((c2 & 0xFF) - (c1 & 0xFF)) * i;
	return (red << 16 | green << 8 | blue);
}

static void	draw_line(t_data *data, t_line l, t_vars *v)
{
	float	x;
	float	y;
	float	step;
	float	i;
	int		color;

	l.start.x += (v->screen_width / 2 + v->map->offset_x);
	l.start.y += (v->screen_height / 2 + v->map->offset_y);
	l.end.x += (v->screen_width / 2 + v->map->offset_x);
	l.end.y += (v->screen_height / 2 + v->map->offset_y);
	x = l.start.x;
	y = l.start.y;
	step = 1 / sqrt(pow(l.end.x - l.start.x, 2) + pow(l.end.y - l.start.y, 2));
	i = 0;
	while (i < 1)
	{
		x = l.start.x + (l.end.x - l.start.x) * i;
		y = l.start.y + (l.end.y - l.start.y) * i;
		color = interpolate_color(l.start_color, l.end_color, i);
		if (x >= 0 && x < v->screen_width && y >= 0 && y < v->screen_height)
			put_pixel(data, x, y, color);
		i += step;
	}
}

int	render_frame(t_vars *vars)
{
	t_point	*point_list;
	t_data	img;
	int		i;

	img.img = mlx_new_image(vars->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	point_list = get_point_list(vars->map);
	if (!point_list)
		return (ft_printf("%sCouldn't fetch point list%s\n", RED, DEFAULT), 0);
	i = -1;
	while (++i < vars->map->width * vars->map->height)
		point_list[i] = calculate_projection(point_list[i], vars->map, i);
	i = vars->map->line_count;
	while (--i >= 0)
	{
		draw_line(&img, (t_line){point_list[vars->map->lines[i].il1], \
			point_list[vars->map->lines[i].il2], vars->map->colors[vars-> \
			map->lines[i].il1], vars->map->colors[vars->map->lines[i].il2] \
		}, vars);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	mlx_destroy_image(vars->mlx, img.img);
	free(point_list);
	return (0);
}
