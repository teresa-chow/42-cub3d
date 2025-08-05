/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_calc01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:30:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 17:06:16 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/* Calculate distance projected on camera direction */
void	calc_cam_dist(t_raycaster *rc)
{
	if (rc->wall == EAST || rc->wall == WEST)
		rc->perp_wall_dist = rc->side_dist_x - rc->delta_dist_x;
	else
		rc->perp_wall_dist = rc->side_dist_y - rc->delta_dist_y;
	if (rc->perp_wall_dist < 0.001)
		rc->perp_wall_dist = 0.001;
}

/* Calculate the point where the ray hit the wall (wall_x)
	floor returns largest int not greater than arg. Hence,
	rc->wall_x -= floor(rc->wall_x) returns only
	the fractional part of wall hit coordinate */
void	calc_wall_x(t_raycaster *rc)
{
	if (rc->wall == EAST || rc->wall == WEST)
		rc->wall_x = rc->cam->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = rc->cam->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
}

/* Calculate height of line to be drawn
   Calculate lowest and highest pixels to fill in current stripe */
void	calc_line_val(t_raycaster *rc)
{
	rc->line_height = (int)(WIN_H / rc->perp_wall_dist);
	rc->line_start = -rc->line_height / 2 + WIN_H / 2;
	if (rc->line_start < 0)
		rc->line_start = 0;
	rc->line_end = rc->line_height / 2 + WIN_H / 2;
	if (rc->line_end >= WIN_H)
		rc->line_end = WIN_H - 1;
}
