/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:00:20 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 00:42:38 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/render_bonus.h"

int	render_frame_bonus(t_raycaster *rc)
{
	get_time_ms(&rc->curr_time_ms);
	if (rc->curr_time_ms - rc->prev_time_ms > 40)
	{
		rc->prev_time_ms = rc->curr_time_ms;
		get_time_ms(&rc->curr_time_ms);
		fill_background(rc);
		raycaster(rc);
		draw_minimap(rc);
		calc_player_movement(rc);
		calc_player_rotation(rc);
		mlx_put_image_to_window(rc->img->mlx,
			rc->img->window, rc->img->img, 0, 0);
	}
	return (0);
}

int	raycaster(t_raycaster *rc)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		calc_ray_pos_dir(rc, x);
		reset_ray_map_coord(rc);
		calc_ray_len(rc);
		calc_step(rc);
		perform_dda(rc);
		calc_cam_dist(rc);
		calc_wall_x(rc);
		calc_line_val(rc);
		draw_vertical_line(rc, x);
		x++;
	}
	return (0);
}
