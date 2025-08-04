/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:26:28 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/04 23:34:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/* atan2 - arctangeant with quadrant correction, used to obtain
angle in radians for vector (x, y) */
void	calc_player_rotation(t_raycaster *rc)
{
	double				angle;
	unsigned int		curr_time;
	static unsigned int	last_move = 0;

	get_time_ms(&curr_time);
	angle = atan2(rc->cam->dir_y, rc->cam->dir_x);
	if (curr_time - last_move > 30)
	{
		if (rc->key_state[4] == 1)
			angle -= 0.05;
		else if (rc->key_state[5] == 1)
			angle += 0.05;
		if (rc->key_state[4] == 1 || rc->key_state[5] == 1)
		{
			rc->cam->dir_x = cos(angle);
			rc->cam->dir_y = sin(angle);
			last_move = curr_time;
		}
	}
}
