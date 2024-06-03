/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prebuild_matrices.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 15:03:04 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/17 15:03:39 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	z_rotation_matrix(float rotation)
{
	t_matrix	matrix;

	matrix.height = 3;
	matrix.width = 3;
	matrix.matrix[0] = cos(rotation);
	matrix.matrix[1] = -sin(rotation);
	matrix.matrix[2] = 0;
	matrix.matrix[3] = sin(rotation);
	matrix.matrix[4] = cos(rotation);
	matrix.matrix[5] = 0;
	matrix.matrix[6] = 0;
	matrix.matrix[7] = 0;
	matrix.matrix[8] = 1;
	return (matrix);
}

t_matrix	y_rotation_matrix(float rotation)
{
	t_matrix	matrix;

	matrix.height = 3;
	matrix.width = 3;
	matrix.matrix[0] = cos(rotation);
	matrix.matrix[1] = 0;
	matrix.matrix[2] = sin(rotation);
	matrix.matrix[3] = 0;
	matrix.matrix[4] = 1;
	matrix.matrix[5] = 0;
	matrix.matrix[6] = -sin(rotation);
	matrix.matrix[7] = 0;
	matrix.matrix[8] = cos(rotation);
	return (matrix);
}

t_matrix	x_rotation_matrix(float rotation)
{
	t_matrix	matrix;

	matrix.height = 3;
	matrix.width = 3;
	matrix.matrix[0] = 1;
	matrix.matrix[1] = 0;
	matrix.matrix[2] = 0;
	matrix.matrix[3] = 0;
	matrix.matrix[4] = cos(rotation);
	matrix.matrix[5] = -sin(rotation);
	matrix.matrix[6] = 0;
	matrix.matrix[7] = sin(rotation);
	matrix.matrix[8] = cos(rotation);
	return (matrix);
}

t_matrix	projection_matrix(void)
{
	t_matrix	matrix;

	matrix.height = 3;
	matrix.width = 3;
	matrix.matrix[0] = 1;
	matrix.matrix[1] = 0;
	matrix.matrix[2] = 0;
	matrix.matrix[3] = 0;
	matrix.matrix[4] = 0;
	matrix.matrix[5] = 1;
	matrix.matrix[6] = 0;
	matrix.matrix[7] = 0;
	matrix.matrix[8] = 0;
	matrix.matrix[9] = 0;
	matrix.matrix[10] = 0;
	matrix.matrix[11] = 0;
	return (matrix);
}
