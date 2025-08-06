/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:48:42 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 09:23:28 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/render_bonus.h"

static void	grid_dda(t_raycaster *rc, int y, int x, t_dda *dda);
static void	grid_loop(t_raycaster *rc, int y, int x, t_dda *dda);

/* Grid */
void	draw_minimap_grid(t_raycaster *rc, t_dda *dda)
{
	int	x;
	int	y;

	y = 0;
	if (dda->spacing == 1)
		return ;
	while (y < rc->world->map_len)
	{
		x = 0;
		while (x < rc->world->map_wid)
		{
			grid_dda(rc, y, x, dda);
			x++;
		}
		y++;
	}
}

static void	grid_dda(t_raycaster *rc, int y, int x, t_dda *dda)
{
	dda->dx = (x + 1) * dda->spacing - x * dda->spacing;
	dda->dy = (y + 1) * dda->spacing - y * dda->spacing;
	if (fabsf(dda->dx) > fabsf(dda->dy))
		dda->step = fabsf(dda->dx);
	else
		dda->step = fabsf(dda->dy);
	dda->x_inc = dda->dx / dda->step;
	dda->y_inc = dda->dy / dda->step;
	grid_loop(rc, y, x, dda);
}

static void	grid_loop(t_raycaster *rc, int y, int x, t_dda *dda)
{
	int	i;

	dda->y1 = y * dda->spacing;
	dda->x1 = x * dda->spacing;
	i = 0;
	while (i <= dda->step)
	{
		pixel_put(rc->img, roundf(dda->x1) + dda->x_ofs,
			roundf(dda->y1) + dda->y_ofs, GRAY);
		dda->y1 += dda->y_inc;
		i++;
	}
	i = 0;
	while (i <= dda->step)
	{
		pixel_put(rc->img, roundf(dda->x1) + dda->x_ofs,
			roundf(dda->y1) + dda->y_ofs, GRAY);
		dda->x1 += dda->x_inc;
		i++;
	}
}
