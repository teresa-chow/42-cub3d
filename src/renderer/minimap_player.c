/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:30:54 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 12:27:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	draw_gaze(t_raycaster *rc, float spacing);

/* Player position */
void	draw_player(t_raycaster *rc, float spacing)
{
	int	radius;
	int	y;
	int	x;
	int	dx;

	radius = spacing / 4;
	y = -radius;
	while (y <= radius)
	{
		dx = (int)sqrtf(radius * radius - y * y);
		x = -dx;
		while (x <= dx)
		{
			pixel_put(rc->img, spacing * rc->cam->pos_x + x
				+ (WIN_W - rc->world->map_wid * spacing),
				spacing * rc->cam->pos_y + y
				+ (WIN_H - rc->world->map_len * spacing), YELLOW);
			x++;
		}
		y++;
	}
	draw_gaze(rc, spacing);
}

/* Player direction */
static void	draw_gaze(t_raycaster *rc, float spacing)
{
	int		i;
	t_dda	dda;

	dda.dx = rc->cam->dir_x * (spacing / 1.25);
	dda.dy = rc->cam->dir_y * (spacing / 1.25);
	dda.x_ofs = WIN_W - rc->world->map_wid * spacing;
	dda.y_ofs = WIN_H - rc->world->map_len * spacing;
	if (fabsf(dda.dx) > fabsf(dda.dy))
		dda.step = fabsf(dda.dx);
	else
		dda.step = fabsf(dda.dy);
	dda.x_inc = dda.dx / dda.step;
	dda.y_inc = dda.dy / dda.step;
	i = 0;
	dda.x1 = spacing * rc->cam->pos_x;
	dda.y1 = spacing * rc->cam->pos_y;
	while (i <= dda.step)
	{
		pixel_put(rc->img, dda.x1 + dda.x_ofs, dda.y1 + dda.y_ofs, MAGENTA);
		dda.x1 += dda.x_inc;
		dda.y1 += dda.y_inc;
		i++;
	}
}
