/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_calc01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:30:30 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/17 13:01:00 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/* Calculate height of line to be drawn
   Calculate lowest and highest pixels to fill in current stripe */
void	calc_line_val(t_raycaster *rc)
{
	rc->line_height = (int)(WIN_H / rc->perp_wall_dist);
	rc->line_start = -rc->line_height / 2 + WIN_H / 2;
	if (rc->line_start < 0)
		rc->line_start = 0;
	rc->line_end = rc->line_height / 2 + WIN_H / 2;
	if (rc->line_end >= WIN_H)
		rc->line_end = WIN_H - 1;
}
