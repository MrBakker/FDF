/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 17:11:01 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/17 15:47:36 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_matrix	multiply_matrix(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	result.height = a.height;
	result.width = b.width;
	i = -1;
	while (++i < a.height)
	{
		j = -1;
		while (++j < b.width)
		{
			result.matrix[i * result.width + j] = 0;
			k = -1;
			while (++k < a.width)
				result.matrix[i * result.width + j] += \
					a.matrix[i * a.width + k] * b.matrix[k * b.width + j];
		}
	}
	return (result);
}

static t_matrix	point_to_matrix(t_point point)
{
	t_matrix	matrix;

	matrix.height = 3;
	matrix.width = 1;
	matrix.matrix[0] = point.x;
	matrix.matrix[1] = point.y;
	matrix.matrix[2] = point.z;
	return (matrix);
}

t_point	calculate_projection(t_point point, t_map *map, int recalculate_matrix)
{
	static t_matrix	x_rotation;
	static t_matrix	y_rotation;
	static t_matrix	z_rotation;
	t_matrix		matrix;

	if (!recalculate_matrix || x_rotation.height == 0)
	{
		x_rotation = x_rotation_matrix(map->x_rotation);
		y_rotation = y_rotation_matrix(map->y_rotation);
		z_rotation = z_rotation_matrix(map->z_rotation);
	}
	matrix = point_to_matrix(point);
	matrix = multiply_matrix(z_rotation, matrix);
	matrix = multiply_matrix(y_rotation, matrix);
	matrix = multiply_matrix(x_rotation, matrix);
	matrix = multiply_matrix(projection_matrix(), matrix);
	return ((t_point){matrix.matrix[0], matrix.matrix[1], 0});
}
