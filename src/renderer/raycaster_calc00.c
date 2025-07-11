/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_calc00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:31:02 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/11 17:12:00 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/* Calculate ray position and direction */
void	calc_ray_pos_dir(t_raycaster *rc, int x)
{
	rc->cam_x = 2 * x / (double)WIN_W - 1;
	rc->ray_dir_x = rc->cam->dir_x + rc->plane_x * rc->cam_x;
	rc->ray_dir_y = rc->cam->dir_y + rc->plane_y * rc->cam_x;
}

/* Calculate ray length (from current position to next x or y side) */
void	calc_ray_len(t_raycaster *rc)
{
	if (rc->ray_dir_x == 0)
		rc->delta_dist_x = 1e30;
	else
		rc->delta_dist_x = 1 / rc->ray_dir_x;
	if (rc->ray_dir_y == 0)
		rc->delta_dist_y = 1e30;
	else
		rc->delta_dist_y = 1 / rc->ray_dir_y;
}

/* Calculate step and side_dist:
ray length from current position to next x/y-side */
void	calc_step(t_raycaster *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->cam->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->cam->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->cam->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->cam->pos_y) * rc->delta_dist_y;
	}
}

/* Perform Digital Differential Analysis (DDA) */
void	perform_dda(t_raycaster *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->wall = EAST_WEST;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->wall = NORTH_SOUTH;
		}
		if (rc->world->map[rc->map_x][rc->map_y] == '1')
			rc->hit = 1;
	}
}

/* Calculate distance projected on camera direction */
void	calc_cam_dist(t_raycaster *rc)
{
	if (rc->wall == EAST_WEST)
		rc->perp_wall_dist = rc->side_dist_x - rc->delta_dist_x;
	else
		rc->perp_wall_dist = rc->side_dist_y - rc->delta_dist_y;
}