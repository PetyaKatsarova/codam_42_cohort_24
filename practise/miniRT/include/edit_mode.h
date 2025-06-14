/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:44:18 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/27 12:30:30 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_MODE_H
# define EDIT_MODE_H

# include <stdbool.h>
# include "mathRT.h"
# include "shape.h"

typedef struct s_scene t_scene;


# define CAM_SPEED 0.5
# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_O 111
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_Q 113
#  define KEY_E 101
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define KEY_P 112
#  define KEY_C 99
#  define KEY_TAB 65289
#  define KEY_SPACE 32
#  define KEY_R 114
#  define KEY_M 109
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_6 54
#  define KEY_7 55
#  define KEY_8 56
#  define KEY_9 57
#  define KEY_RETURN 65293
#  define KEY_SHIFT 65505
#  define LEFT_MOUSE_DOWN 1
#  define KEY_T 116
#  define KEY_X 120
#  define KEY_Y 121
#  define KEY_Z 122
#  define KEY_L 108
#  define KEY_J 106
#  define KEY_H 104
# else
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_O 31
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_Q 12
#  define KEY_E 14
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_P 35
#  define KEY_C 8
#  define KEY_TAB 48
#  define KEY_SPACE 49
#  define KEY_R 15
#  define KEY_M 46
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_6 22
#  define KEY_7 26
#  define KEY_8 28
#  define KEY_9 25
#  define KEY_RETURN 36
#  define KEY_SHIFT 257
#  define LEFT_MOUSE_DOWN 1
#  define KEY_T 17
#  define KEY_J 38
#  define KEY_X 7
#  define KEY_Y 16
#  define KEY_Z 6
#  define KEY_L 37
#  define KEY_H 4
# endif
# define ON_DESTROY 17

// Forward declaration
struct						s_ray;
typedef struct s_ray		t_ray;

typedef struct s_keys		t_keys;
struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	q;
	bool	e;
	bool	plus;
	bool	minus;
	bool	tab;
	bool	c;
	bool	shift;
	bool	x;
	bool	y;
	bool	z;
	bool	o;
};

int			mouse_rotate(t_scene *scene);
void		rotate_x(t_scene *scene, t_mat4 *rot_mat, double deg);
void		rotate_y(t_scene *scene, t_mat4 *rot_mat, double deg);
void		rotate_z(t_scene *scene, t_mat4 *rot_mat, double deg);
int			mouse_down(int key_code, int x, int y, t_scene *scene);
int			mouse_up(int key_code, int x, int y, t_scene *scene);
int			key_press(int key, t_scene *scene);
int			key_release(int key, t_scene *scene);
int			render_loop(t_scene *scene);
int			close_window(t_scene *scene);
void		look_at(t_scene *scene, t_shape *shape);
void		show_light_banner(t_scene *scene);
void		rotate_along_mouse_axis(t_scene *scene);
void		drag_along_plane(t_scene *scene, t_ray *mouse_selection);
void		toggle_edit_mode(int key, t_scene *scene);
void		select_shape(int key, t_scene *scene);
void		spawn_shape(t_scene *scene);
void		toggle_reflections(t_scene *scene);
void		toggle_keys_held(int key, t_scene *scene, bool on_off);
bool		is_toggle_key(int key, t_scene *scene);
void		toggle_shape(t_scene *scene);
void		camera_controls(t_scene *scene);
void		move_cam(t_scene *scene);
void		move_object_fwd(t_scene *scene, t_shape *shape);
void		move_object_h(t_scene *scene, t_shape *shape);
void		transform_object(t_scene *scene);
void		light_controls(t_scene *scene);
void		look_at_animation(t_scene *scene);
bool		is_loop_hook_key(t_scene *scene);
void		move_object_h(t_scene *scene, t_shape *shape);
void		move_object_v(t_scene *scene, t_shape *shape);
t_vector	*sphere_to_xyz(t_vector *vec, double phi, double theta, double r);
void		change_height(t_scene *scene, t_shape *shape);
void		scale_cube_sides(t_scene *scene, t_shape *shape);
void		scale_object(t_scene *scene, t_shape *shape);

#endif
