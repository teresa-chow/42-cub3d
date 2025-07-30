/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:30:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 13:41:51 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	get_bg_color(t_raycaster *rc, float y1, int *color);

void	fill_background(t_raycaster *rc)
{
	t_dda	dda;
	int		color;
	int		i;
	int		j;

	ft_bzero(&dda, sizeof(t_dda));
	if (WIN_W > WIN_H)
		dda.step = WIN_W;
	else
		dda.step = WIN_H;
	j = 0;
	while (j <= dda.step)
	{
		get_bg_color(rc, dda.y1, &color);
		i = 0;
		dda.x1 = 0;
		while (i <= dda.step)
		{
			pixel_put(rc->img, dda.x1, dda.y1, color);
			dda.x1 += (float)WIN_W / dda.step;
			i++;
		}
		dda.y1 += (float)WIN_H / dda.step;
		j++;
	}
}

static void	get_bg_color(t_raycaster *rc, float y1, int *color)
{
	if (y1 < (float)WIN_H / 2)
		*color = rc->world->sky;
	else
		*color = rc->world->ground;
}

void	pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if ((x > 0 && y > 0) && (x < WIN_W && y < WIN_H))
	{
		dst = img->addr + (y * img->line_len + x * (img->bits_pxl / 8));
		*(int *)dst = color;
	}
	return ;
}
