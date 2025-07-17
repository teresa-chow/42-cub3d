/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:30:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/17 12:50:57 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

//refactor - use same function for block printing as in minimap.c?
void	fill_background(t_raycaster *rc)
{
	int	i;
	int	j = 0;
	t_dda	dda;

	ft_bzero(&dda, sizeof(t_dda));
	dda.dx = WIN_W;
	dda.dy = WIN_H / 2;
	if (fabsf(dda.dx) > fabsf(dda.dy))
		dda.step = fabsf(dda.dx);
	else
		dda.step = fabsf(dda.dy);
	dda.x_inc = dda.dx / dda.step;
	dda.y_inc = dda.dy / dda.step;
	while (j <= dda.step)
	{
		dda.y1 += dda.y_inc;
		dda.x1 = 0;
		i = 0;
		while (i <= dda.step)
		{
			pixel_put(rc->img, dda.x1, dda.y1, rc->world->sky);
			dda.x1 += dda.x_inc;
			i++;
		}
		j++;
	}
	j = 0;
	dda.y1 = WIN_H / 2; 
	while (j <= dda.step)
	{
		dda.y1 += dda.y_inc;
		dda.x1 = 0;
		i = 0;
		while (i <= dda.step)
		{
			pixel_put(rc->img, dda.x1, dda.y1, rc->world->ground);
			dda.x1 += dda.x_inc;
			i++;
		}
		j++;
	}
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
