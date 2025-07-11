/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:30:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/11 17:32:45 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

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

/* Bucket tool */
//flood_fill()