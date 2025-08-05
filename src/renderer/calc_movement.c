/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:40:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:45 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	move_forward(t_raycaster *rc, unsigned int *last_move,
				double step);
static void	move_left(t_raycaster *rc, unsigned int *last_move, double step);
static void	move_backwards(t_raycaster *rc, unsigned int *last_move,
				double step);
static void	move_right(t_raycaster *rc, unsigned int *last_move, double step);

void	calc_player_movement(t_raycaster *rc)
{
	unsigned int		curr_time;
	static unsigned int	last_move = 0;
	double				step;

	step = 0.066;
	get_time_ms(&curr_time);
	if (curr_time - last_move > 30)
	{
		if (rc->key_state[0] == 1)
			move_forward(rc, &last_move, step);
		if (rc->key_state[1] == 1)
			move_left(rc, &last_move, step);
		if (rc->key_state[2] == 1)
			move_backwards(rc, &last_move, step);
		if (rc->key_state[3] == 1)
			move_right(rc, &last_move, step);
	}
}

/* Player movement helper functions (movement uses direction vector) */
static void	move_forward(t_raycaster *rc, unsigned int *last_move, double step)
{
	double	y;
	double	x;

	y = rc->cam->pos_y + rc->cam->dir_y * step;
	x = rc->cam->pos_x + rc->cam->dir_x * step;
	if (rc->world->map[(int)y][(int)rc->cam->pos_x] != '1')
		rc->cam->pos_y = y;
	if (rc->world->map[(int)rc->cam->pos_y][(int)x] != '1')
		rc->cam->pos_x = x;
	get_time_ms(last_move);
}

static void	move_left(t_raycaster *rc, unsigned int *last_move, double step)
{
	double	y;
	double	x;

	y = rc->cam->pos_y - rc->cam->dir_x * step;
	x = rc->cam->pos_x + rc->cam->dir_y * step;
	if (rc->world->map[(int)y][(int)rc->cam->pos_x] != '1')
		rc->cam->pos_y = y;
	if (rc->world->map[(int)rc->cam->pos_y][(int)x] != '1')
		rc->cam->pos_x = x;
	get_time_ms(last_move);
}

static void	move_backwards(t_raycaster *rc, unsigned int *last_move,
	double step)
{
	double	y;
	double	x;

	y = rc->cam->pos_y - rc->cam->dir_y * step;
	x = rc->cam->pos_x - rc->cam->dir_x * step;
	if (rc->world->map[(int)y][(int)rc->cam->pos_x] != '1')
		rc->cam->pos_y = y;
	if (rc->world->map[(int)rc->cam->pos_y][(int)x] != '1')
		rc->cam->pos_x = x;
	get_time_ms(last_move);
}

static void	move_right(t_raycaster *rc, unsigned int *last_move, double step)
{
	double	y;
	double	x;

	y = rc->cam->pos_y + rc->cam->dir_x * step;
	x = rc->cam->pos_x - rc->cam->dir_y * step;
	if (rc->world->map[(int)y][(int)rc->cam->pos_x] != '1')
		rc->cam->pos_y = y;
	if (rc->world->map[(int)rc->cam->pos_y][(int)x] != '1')
		rc->cam->pos_x = x;
	get_time_ms(last_move);
}
