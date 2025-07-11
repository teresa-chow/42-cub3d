/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:12:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/11 19:51:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/*static void calc_minimap_spacing(t_raycaster *rc, float *spacing);

void    draw_minimap(t_raycaster *rc)
{
	float	spacing;
	int	x;
	int	y;

	calc_minimap_spacing(rc, &spacing);
	y = 0;
	while (y < rc->world->map_len)
	{
		x = 0;
		while (x < rc->world->map_wid - 1)
		{
			line_drawing_dda(rc, y, x, spacing);
			x++;
		}
		line_drawing_dda(rc, y, x, spacing); // ?
		y++;
	}
}

static void calc_minimap_spacing(t_raycaster *rc, float *spacing)
{
	if (rc->world->map_len > rc->world->map_wid)
		spacing = (WIN_H / 4) / rc->world->map_len;
	else
		spacing = (WIN_W / 5) / rc->world->map_wid;
}

void	line_drawing_dda(t_raycaster *rc, int y, int x, float spacing)
{
	int			i;
	t_dda		dda;

	dda.dx = (x + 1) * spacing - point->x;
	dda.dy = next_point->y - point->y;
	if (fabsf(dda.dx) > fabsf(dda.dy))
		dda.step = fabsf(dda.dx);
	else
		dda.step = fabsf(dda.dy);
	dda.x_inc = dda.dx / dda.step;
	dda.y_inc = dda.dy / dda.step;
	i = 0;
	dda.x1 = point->x;
	dda.y1 = point->y;
	while (i <= dda.step)
	{
		pixel_put(img, roundf(dda.x1), roundf(dda.y1), point->color);
		dda.x1 += dda.x_inc;
		dda.y1 += dda.y_inc;
		i++;
	}
}*/
