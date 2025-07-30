/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:00:20 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:14:49 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	draw_vertical_line(t_raycaster *rc, int x); //tmp

int	render_frame(t_raycaster *rc)
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

int	raycaster(t_raycaster *rc) // check return value upon error
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
		calc_line_val(rc);
		draw_vertical_line(rc, x);
		x++;
	}
	return (0);
}

// tmp ------------------------------------------------------
/*static void	draw_vertical_line(t_raycaster *rc, int x)
{
	int		i;
	t_dda	dda;
	int		color;

	if (rc->wall == EAST_WEST)
		color = YELLOW;
	else
		color = 16758272;
	ft_bzero(&dda, sizeof(t_dda));
	dda.dy = rc->line_end - rc->line_start;
	dda.step = fabsf(dda.dy);
	dda.y_inc = dda.dy / dda.step;
	i = 0;
	dda.x1 = x;
	dda.y1 = rc->line_start;
	while (i <= dda.step)
	{
		pixel_put(rc->img, dda.x1, dda.y1, color);
		dda.y1 += dda.y_inc;
		i++;
	}
}*/

static void	draw_vertical_line(t_raycaster *rc, int x)
{
	int		y;
	int		color;

	if (rc->wall == EAST || rc->wall == WEST)
		color = YELLOW;
	else
		color = 16758272;
	y = rc->line_start;
	while (y <= rc->line_end)
	{
		pixel_put(rc->img, x, y, color);
		y++;
	}
}
