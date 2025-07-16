/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:00:20 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/16 00:11:36 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	assign_colors(t_raycaster *rc); //tmp

int	render_frame(t_raycaster *rc)
{
    //raycaster(rc);
	draw_minimap(rc);
    mlx_put_image_to_window(rc->img->mlx, rc->img->window, rc->img->img, 0, 0);
	return (0);
}

int	raycaster(t_raycaster *rc) // check return value upon error
{
	int	x;

	x = 0;
	while (x < rc->world->map_wid)
	{
		calc_ray_pos_dir(rc, x);
		rc->map_x = (int)rc->cam->pos_x; //coordinates of current map position
		rc->map_y = (int)rc->cam->pos_y;
		calc_ray_len(rc);
		calc_step(rc);
		perform_dda(rc);
		calc_cam_dist(rc);
		calc_line_val(rc);
		assign_colors(rc); //tmp
		x++;
	}
	return (0);
}

//TODO: delete tmp function
static void	assign_colors(t_raycaster *rc)
{
	pixel_put(rc->img, rc->line_start, rc->line_end, 14876450);
}
