/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_calc00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:31:02 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 09:44:38 by tchow-so         ###   ########.fr       */
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

/* Reset map and hit values for each ray / vertical line */
void	reset_ray_map_coord(t_raycaster *rc)
{
	rc->map_x = (int)rc->cam->pos_x;
	rc->map_y = (int)rc->cam->pos_y;
	rc->hit = 0;
}

/* Calculate ray length (from current position to next x or y side)
1e30 is a stand-in for "infinite distance" when ray is parallel to an axis */
void	calc_ray_len(t_raycaster *rc)
{
	if (rc->ray_dir_x == 0)
		rc->delta_dist_x = 1e30;
	else
		rc->delta_dist_x = 1 / fabs(rc->ray_dir_x);
	if (rc->ray_dir_y == 0)
		rc->delta_dist_y = 1e30;
	else
		rc->delta_dist_y = 1 / fabs(rc->ray_dir_y);
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
		if (fabs(rc->side_dist_x) < fabs(rc->side_dist_y))
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			if (rc->step_x > 0)
				rc->wall = EAST;
			else
				rc->wall = WEST;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			if (rc->step_y > 0)
				rc->wall = NORTH;
			else
				rc->wall = SOUTH;
		}
		if (rc->world->map[rc->map_y][rc->map_x] == '1')
			rc->hit = 1;
	}
}
