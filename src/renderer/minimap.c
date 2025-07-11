/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:12:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/11 18:48:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/*void    draw_minimap(t_raycaster *rc)
{
	//check if map width or height is bigger
	//calculate them proportionally to WIN_W and WIN_H (set max width or height)
	//consider that value to know dimension of grid
	//run through map while drawing it
    line_drawing_dda(rc->img)
    rc->world->map_len //contains the number of cells, no the spacing between them,
	that has to be calculated
    rc->world->map_wid //same
}

void	line_drawing_dda(t_data *img, //point and next_point)
{
	int			i;
	t_dda		dda;

	dda.dx = next_point->x - point->x;
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
