/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separating_axis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:49:20 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/05 21:04:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// From Real Time Collision Detection (2005) pg.103 - 105
bool	test_box_axes(t_shape *b1, t_shape *b2, t_vector *resolution)
{
	t_vector	b1_u[3];
	b1_u[0].x = b1->added_rots[0][0];
	b1_u[0].y = b1->added_rots[1][0];
	b1_u[0].z = b1->added_rots[2][0];
	b1_u[0].w = 0;
	normalize_vec(&b1_u[0]);
	b1_u[1].x = b1->added_rots[0][1];
	b1_u[1].y = b1->added_rots[1][1];
	b1_u[1].z = b1->added_rots[2][1];
	b1_u[1].w = 0;
	normalize_vec(&b1_u[1]);
	b1_u[2].x = b1->added_rots[0][2];
	b1_u[2].y = b1->added_rots[1][2];
	b1_u[2].z = b1->added_rots[2][2];
	b1_u[2].w = 0;
	normalize_vec(&b1_u[2]);
	t_vector	b2_u[3];
	b2_u[0].x = b2->added_rots[0][0];
	b2_u[0].y = b2->added_rots[1][0];
	b2_u[0].z = b2->added_rots[2][0];
	b2_u[0].w = 0;
	normalize_vec(&b2_u[0]);
	b2_u[1].x = b2->added_rots[0][1];
	b2_u[1].y = b2->added_rots[1][1];
	b2_u[1].z = b2->added_rots[2][1];
	b2_u[1].w = 0;
	normalize_vec(&b2_u[1]);
	b2_u[2].x = b2->added_rots[0][2];
	b2_u[2].y = b2->added_rots[1][2];
	b2_u[2].z = b2->added_rots[2][2];
	b2_u[2].w = 0;
	normalize_vec(&b2_u[2]);
	t_mat4	rot;
	rot[0][0] = dot_product(&b1_u[0], &b2_u[0]);
	rot[0][1] = dot_product(&b1_u[0], &b2_u[1]);
	rot[0][2] = dot_product(&b1_u[0], &b2_u[2]);
	rot[0][3] = 0;
	rot[1][0] = dot_product(&b1_u[1], &b2_u[0]);
	rot[1][1] = dot_product(&b1_u[1], &b2_u[1]);
	rot[1][2] = dot_product(&b1_u[1], &b2_u[2]);
	rot[1][3] = 0;
	rot[2][0] = dot_product(&b1_u[2], &b2_u[0]);
	rot[2][1] = dot_product(&b1_u[2], &b2_u[1]);
	rot[2][2] = dot_product(&b1_u[2], &b2_u[2]);
	rot[2][3] = 0;
	rot[3][0] = 0;
	rot[3][1] = 0;
	rot[3][2] = 0;
	rot[3][3] = 1;
	t_vector	center_distance;
	sub_vec(&center_distance, &b2->origin, &b1->origin);
	double	t[3];
	t[0] = dot_product(&center_distance, &b1_u[0]);
	t[1] = dot_product(&center_distance, &b1_u[1]);
	t[2] = dot_product(&center_distance, &b1_u[2]);
	t_mat4	abs_rot;
	int i = 0;
	int j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			abs_rot[i][j] = fabs(rot[i][j]) + EPSILON;
			j++;
		}
		i++;
	}
	double	b1_e[3];
	b1_e[0] = b1->props.scale.x;
	b1_e[1] = b1->props.scale.y;
	b1_e[2] = b1->props.scale.z;
	double	b2_e[3];
	b2_e[0] = b2->props.scale.x;
	b2_e[1] = b2->props.scale.y;
	b2_e[2] = b2->props.scale.z;
	double	res_distance = INFINITY;
	t_vector	res_axis;
	// res_axis = b1_u[0];
	ft_bzero(&res_axis, sizeof(t_vector));
	double	ra, rb;
	for (int i = 0; i < 3; i++) {
		ra = b1_e[i];
		rb = b2_e[0] * abs_rot[i][0] + b2_e[1] * abs_rot[i][1] + b2_e[2] * abs_rot[i][2];
		if (fabs(t[i]) > (ra + rb)) return false;
		if (((ra + rb) - fabs(t[i])) < res_distance)
		{
			// res_axis.x = abs_rot[i][0];
			// res_axis.y = abs_rot[i][1];
			// res_axis.z = abs_rot[i][2];
			res_distance = (ra + rb) - fabs(t[i]);
			res_axis = b1_u[i];
			if (t[i] < 0)
			{
				negate_vec(&res_axis, &res_axis);
			}
		}
	}
// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = b1_e[0] * abs_rot[0][i] + b1_e[1] * abs_rot[1][i] + b1_e[2] * abs_rot[2][i];
		rb = b2_e[i];
		if (fabs(t[0] * rot[0][i] + t[1] * rot[1][i] + t[2] * rot[2][i]) > (ra + rb)) return false;
		if (((ra + rb) - fabs(t[0] * rot[0][i] + t[1] * rot[1][i] + t[2] * rot[2][i])) < res_distance)
		{
			res_distance = (ra + rb) - fabs(t[0] * rot[0][i] + t[1] * rot[1][i] + t[2] * rot[2][i]);
			res_axis = b2_u[i];
			if ((t[0] * rot[0][i] + t[1] * rot[1][i] + t[2] * rot[2][i]) < 0)
				negate_vec(&res_axis, &res_axis);
		}
	}
	

	if (resolution != NULL)
	{
		*resolution = res_axis;
		normalize_vec(resolution);
		// t_vector	orient;
		scale_vec(resolution, resolution, res_distance + 0.0001);
	}
	return (true);
}