/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:40:23 by hsarhan           #+#    #+#             */
/*   Updated: 2023/02/27 13:07:36 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <unistd.h>
# include <pthread.h>
# include <signal.h>
# include "../libft/libft.h"
# ifdef __linux__
#  include "../mlx_linux/mlx.h"
#  define LINUX 1
# else
#  include "../mlx/mlx.h"
#  define LINUX 0
# endif
# include "mathRT.h"
# include "color.h"
# include "display.h"
# include "shape.h"
# include "camera.h"
# include "edit_mode.h"
# include "intersections.h"
# include "lights.h"
# include "scene.h"
# include "render.h"
# include "parsing.h"
# include "utils.h"
# include "collisions.h"
# define EPSILON 0.001f

#endif
