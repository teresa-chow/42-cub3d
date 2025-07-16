/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:40:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/16 12:55:23 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	get_time_ms(unsigned int *curr_time);

void	calc_player_movement(t_raycaster *rc)
{
	int					y;
	int					x;
	unsigned int		curr_time;
	static unsigned int	last_move = 0;

	y = (int)rc->cam->pos_y;
	x = (int)rc->cam->pos_x;
	get_time_ms(&curr_time);
	if (curr_time - last_move > 50)
	{
		if (rc->world->map[y - 1][x] != '1' && rc->key_state[0] == 1)
			rc->cam->pos_y -= 1;
		else if (rc->world->map[y][x - 1] != '1' && rc->key_state[1] == 1)
			rc->cam->pos_x -= 1;
		else if (rc->world->map[y + 1][x] != '1' && rc->key_state[2] == 1)
			rc->cam->pos_y += 1;
		else if (rc->world->map[y][x + 1] != '1' && rc->key_state[3] == 1)
			rc->cam->pos_x += 1;
		last_move = curr_time;
	}
}

/* Get time of day to calculate movement cooldown (20 ms) */
static void	get_time_ms(unsigned int *curr_time)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	*curr_time = now.tv_sec * 1e3 + now.tv_usec / 1e3;
}

/*void    calc_player_rotation(t_raycaster *rc)
{
	
}*/