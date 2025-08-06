/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:12:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 09:33:15 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/render_bonus.h"

static void	calc_minimap_spacing(t_raycaster *rc, float *spacing);
static void	filling_dda(t_raycaster *rc, int y, int x, t_dda *dda);
static void	filling_loop(t_raycaster *rc, int y, int x, t_dda *dda);
static void	get_minimap_color(t_raycaster *rc, int y, int x, int *color);

void	draw_minimap(t_raycaster *rc)
{
	int		x;
	int		y;
	t_dda	dda;

	ft_bzero(&dda, sizeof(t_dda));
	calc_minimap_spacing(rc, &dda.spacing);
	dda.x_ofs = WIN_W - rc->world->map_wid * dda.spacing;
	dda.y_ofs = WIN_H - rc->world->map_len * dda.spacing;
	y = 0;
	while (y < rc->world->map_len)
	{
		x = 0;
		while (x < rc->world->map_wid)
		{
			filling_dda(rc, y, x, &dda);
			x++;
		}
		y++;
	}
	draw_minimap_grid(rc, &dda);
	draw_player(rc, dda.spacing);
}

/* Minimap display dimensions */
static void	calc_minimap_spacing(t_raycaster *rc, float *spacing)
{
	if (rc->world->map_len > rc->world->map_wid)
		*spacing = (float)((WIN_H / 4) / rc->world->map_len);
	else
		*spacing = (float)((WIN_W / 5) / rc->world->map_wid);
	if (*spacing < 1)
		*spacing = 1;
}

/* Walls and walkable area */
static void	filling_dda(t_raycaster *rc, int y, int x, t_dda *dda)
{
	dda->dx = (x + 1) * dda->spacing - x * dda->spacing;
	dda->dy = (y + 1) * dda->spacing - y * dda->spacing;
	if (fabsf(dda->dx) > fabsf(dda->dy))
		dda->step = fabsf(dda->dx);
	else
		dda->step = fabsf(dda->dy);
	dda->x_inc = dda->dx / dda->step;
	dda->y_inc = dda->dy / dda->step;
	filling_loop(rc, y, x, dda);
}

static void	filling_loop(t_raycaster *rc, int y, int x, t_dda *dda)
{
	int	i;
	int	j;
	int	color;

	dda->y1 = y * dda->spacing;
	get_minimap_color(rc, y, x, &color);
	j = 0;
	while (j <= dda->step)
	{
		pixel_put(rc->img, roundf(dda->x1) + dda->x_ofs,
			roundf(dda->y1) + dda->y_ofs, color);
		dda->y1 += dda->y_inc;
		dda->x1 = x * dda->spacing;
		i = 0;
		while (i < dda->step)
		{
			pixel_put(rc->img, roundf(dda->x1) + dda->x_ofs,
				roundf(dda->y1) + dda->y_ofs, color);
			dda->x1 += dda->x_inc;
			i++;
		}
		j++;
	}
}

static void	get_minimap_color(t_raycaster *rc, int y, int x, int *color)
{
	if (rc->world->map[y][x] == '0')
		*color = BLACK;
	else if (rc->world->map[y][x] == '1')
		*color = WHITE;
	else
		*color = GRAY;
}
