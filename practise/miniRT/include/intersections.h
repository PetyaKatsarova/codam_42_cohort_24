/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:19:12 by mkhan             #+#    #+#             */
/*   Updated: 2023/02/27 12:31:33 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "mathRT.h"
# include <stdbool.h>
# include "shape.h"
# include "camera.h"

/**
 * @brief A ray being cast from the screen
 * @param origin The ray starting point
 * @param direction The direction where the ray is being projected
 */
typedef struct s_ray			t_ray;
struct s_ray
{
	t_vector	origin;
	t_vector	dir;
};

/**
 * @brief Contains the time value of an intersection of a ray with an object,
 * along with the object that it intersected with
 * @param time The t value of the intersection
 * @param shape A pointer to the object that the ray intersected with
 */
typedef struct s_intersect		t_intersection;
struct s_intersect
{	
	double		time;
	t_shape		*shape;
	t_vector	point;
	t_vector	normal;
	t_vector	eye;
	t_vector	over_point;
	t_vector	reflect_vec;
	bool		inside;
};

/**
 * @brief A wrapper around an array of intersections
 * @param arr Array of intersections
 * @param count Number of intersections in the array
 */
typedef struct s_intersections	t_intersections;
struct s_intersections
{
	t_intersection	arr[200];
	int				count;
};

bool			intersect(t_shape *shape, const t_ray *ray,
					t_intersections *xs);

t_intersection	*hit(t_intersections *xs);

void			ray_position(t_vector *pos, const t_ray *ray, double time);

t_vector		normal_at(const t_shape *shape, const t_vector *itx_point);

void			ray_from_cam(t_ray *ray, const t_camera *cam, double x,
					double y);
bool			intersect_cylinder(const t_ray *ray, t_shape *shape,
					t_intersections *xs);
bool			intersect_cone(const t_ray *ray, t_shape *shape,
					t_intersections *xs);
void			spherical_map(double *u, double *v, t_vector *point);
void			cylindrical_map(double *u, double *v, t_vector *point);
void			cubical_map(double *u, double *v, t_vector *point);
bool			intersect_cube(t_shape *shape, t_ray *ray, t_intersections *xs);
bool			test_box_axes(t_shape *b1, t_shape *b2, t_vector *resolution);
t_vector		cube_normal(const t_shape *shape, const t_vector *itx_point);
void			calculate_orientation(t_mat4 *rot_transform, t_shape *shape);
int				intersect_shadowed(t_shape *shape, const t_ray *ray,
					t_intersections *xs);

t_vector		box_furthest_point(const t_vector *dir, const t_shape *box);
t_vector		cylinder_furthest_point(const t_vector *dir,
					const t_shape *cyl);
t_vector		normal_from_texture(const t_shape *shape,
					const t_vector *itx_point);
t_vector		get_texture_coords(const t_shape *shape, double u, double v,
					t_vector *normal);
t_vector		normal_from_texture(const t_shape *shape,
					const t_vector *itx_point);
t_vector		normal_at(const t_shape *shape, const t_vector *itx_point);
t_vector		cylinder_normal(const t_shape *shape,
					const t_vector *itx_point);
t_vector		cone_normal(const t_shape *shape, const t_vector *itx_point);
t_vector		plane_normal(const t_shape *shape, const t_vector *itx_point);
t_vector		cube_normal(const t_shape *shape, const t_vector *itx_point);
t_vector		sphere_normal(t_vector *normal, const t_shape *shape,
					const t_vector *itx_point);

#endif
