/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:12:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/13 00:52:10 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void calc_minimap_spacing(t_raycaster *rc, float *spacing);
static void	line_drawing_dda(t_raycaster *rc, int y, int x, float spacing);
static int	get_minimap_color(t_raycaster *rc, int y, int x, int *color);

void    draw_minimap(t_raycaster *rc)
{
	float	spacing;
	int	x;
	int	y;

	calc_minimap_spacing(rc, &spacing);
	y = 0;
	while (y < rc->world->map_len - 1)
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
		*spacing = (float)((WIN_H / 4) / rc->world->map_len);
	else
		*spacing = (float)((WIN_W / 5) / rc->world->map_wid);
}

static void	line_drawing_dda(t_raycaster *rc, int y, int x, float spacing)
{
	int			i;
	int			color;
	t_dda		dda;

	get_minimap_color(rc, y, x, &color);
	dda.dx = (x + 1) * spacing - x * spacing;
	dda.dy = (y + 1) * spacing - y * spacing;
	if (fabsf(dda.dx) > fabsf(dda.dy))
		dda.step = fabsf(dda.dx);
	else
		dda.step = fabsf(dda.dy);
	dda.x_inc = dda.dx / dda.step;
	dda.y_inc = dda.dy / dda.step;
	i = 0;
	dda.x1 = x * spacing;
	dda.y1 = y * spacing;
	while (i <= dda.step)
	{
		pixel_put(rc->img, roundf(dda.x1), roundf(dda.y1), color);
		dda.x1 += dda.x_inc;
		dda.y1 += dda.y_inc;
		i++;
	}
}

static int	get_minimap_color(t_raycaster *rc, int y, int x, int *color)
{
	if (rc->world->map[y][x] == '1')
		color = 16777215;
	else
		color = 0;
}

//draw player