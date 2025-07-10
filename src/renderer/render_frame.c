/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:00:20 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/10 12:13:52 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/*void	pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	if ((x > 0 && y > 0) && (x < WIN_W && y < WIN_H))
	{
		dst = img->addr + (y * img->line_len + x * (img->bits_pxl / 8));
		*(int *)dst = color;
	}
	return ;
}*/