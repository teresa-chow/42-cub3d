/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:40:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/16 16:53:54 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	get_time_ms(unsigned int *curr_time);

/*void	calc_player_movement(t_raycaster *rc)
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
}*/

// Player movement must account for direction
void	calc_player_movement(t_raycaster *rc)
{
	int					x;
	int					y;
	unsigned int		curr_time;
	static unsigned int	last_move = 0;

	get_time_ms(&curr_time);
	if (curr_time - last_move > 50)
	{
		x = round(rc->cam->pos_x + rc->cam->dir_x);
		y = round(rc->cam->pos_y + rc->cam->dir_y);
		if (rc->key_state[0] == 1 && rc->world->map[y][x] != '1')
		{
				rc->cam->pos_x = x;
				rc->cam->pos_y = y;	
		}
		x = round(rc->cam->pos_x - rc->cam->dir_y);
		y = round(rc->cam->pos_y + rc->cam->dir_x);
		if (rc->key_state[1] == 1 && rc->world->map[y][x] != '1')
		{
				rc->cam->pos_x = x;
				rc->cam->pos_y = y;	
		}
		x = round(rc->cam->pos_x - rc->cam->dir_x);
		y = round(rc->cam->pos_y - rc->cam->dir_y);
		if (rc->key_state[2] == 1 && rc->world->map[y][x] != '1')
		{
				rc->cam->pos_x = x;
				rc->cam->pos_y = y;	
		}
		x = round(rc->cam->pos_x + rc->cam->dir_y);
		y = round(rc->cam->pos_y - rc->cam->dir_x);
		if (rc->key_state[3] == 1 && rc->world->map[y][x] != '1')
		{
				rc->cam->pos_x = x;
				rc->cam->pos_y = y;	
		}
		last_move = curr_time;
	}
}

void    calc_player_rotation(t_raycaster *rc)
{
	double				angle;
	unsigned int		curr_time;
	static unsigned int	last_move = 0;

	get_time_ms(&curr_time);
	angle = atan2(rc->cam->dir_y, rc->cam->dir_x); //returns the angle in radians for vector (x, y)
	if (curr_time - last_move > 20)
	{
		if (rc->key_state[4] == 1)
			angle -= 0.1;
		else if (rc->key_state[5] == 1)
			angle += 0.1;
		if (rc->key_state[4] == 1 || rc->key_state[5] == 1)
		{
			rc->cam->dir_x = cos(angle);
			rc->cam->dir_y = sin(angle);
			last_move = curr_time;
		}
	}
}

/* Get time of day to calculate movement cooldown (50 ms) */
static void	get_time_ms(unsigned int *curr_time)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	*curr_time = now.tv_sec * 1e3 + now.tv_usec / 1e3;
}
