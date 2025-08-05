/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:26:28 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 09:44:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	rotate_direction(t_raycaster *rc, double rot);
static void	rotate_camera_plane(t_raycaster *rc, double rot);

/* Calculate player rotation by angle increment (rot)
- this will affect both direction vector and plane vector */
void	calc_player_rotation(t_raycaster *rc)
{
	double				rot;
	unsigned int		curr_time;
	static unsigned int	last_move = 0;
	double				rot_speed;

	rot = 0;
	rot_speed = 0.05;
	get_time_ms(&curr_time);
	if (curr_time - last_move > 30)
	{
		if (rc->key_state[4])
			rot = -rot_speed;
		else if (rc->key_state[5])
			rot = rot_speed;
		if (rot != 0)
		{
			rotate_direction(rc, rot);
			rotate_camera_plane(rc, rot);
			last_move = curr_time;
		}
	}
}

/* Rotate both the direction vector (cam->dir_) and the plane vector
by the same angle increment (rot) */
static void	rotate_direction(t_raycaster *rc, double rot)
{
	double	old_dir_x;

	old_dir_x = rc->cam->dir_x;
	rc->cam->dir_x = rc->cam->dir_x * cos(rot) - rc->cam->dir_y * sin(rot);
	rc->cam->dir_y = old_dir_x * sin(rot) + rc->cam->dir_y * cos(rot);
}

static void	rotate_camera_plane(t_raycaster *rc, double rot)
{
	double	old_plane_x;

	old_plane_x = rc->plane_x;
	rc->plane_x = rc->plane_x * cos(rot) - rc->plane_y * sin(rot);
	rc->plane_y = old_plane_x * sin(rot) + rc->plane_y * cos(rot);
}
