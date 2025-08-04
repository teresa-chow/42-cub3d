/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:40:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/04 23:32:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	move_forward(t_raycaster *rc, unsigned int *last_move);
static void	move_left(t_raycaster *rc, unsigned int *last_move);
static void	move_backwards(t_raycaster *rc, unsigned int *last_move);
static void	move_right(t_raycaster *rc, unsigned int *last_move);

void	calc_player_movement(t_raycaster *rc)
{
	unsigned int		curr_time;
	static unsigned int	last_move = 0;

	get_time_ms(&curr_time);
	if (curr_time - last_move > 30)
	{
		if (rc->key_state[0] == 1)
			move_forward(rc, &last_move);
		if (rc->key_state[1] == 1)
			move_left(rc, &last_move);
		if (rc->key_state[2] == 1)
			move_backwards(rc, &last_move);
		if (rc->key_state[3] == 1)
			move_right(rc, &last_move);
	}
}

/* Player movement helper functions (movement uses direction vector) */
static void	move_forward(t_raycaster *rc, unsigned int *last_move)
{
	int		y;
	int		x;

	y = round(rc->cam->pos_y + rc->cam->dir_y / 15);
	x = round(rc->cam->pos_x + rc->cam->dir_x / 15);
	if (rc->world->map[y][x] != '1')
	{
		rc->cam->pos_y += rc->cam->dir_y / 15;
		rc->cam->pos_x += rc->cam->dir_x / 15;
		get_time_ms(last_move);
	}
}

static void	move_left(t_raycaster *rc, unsigned int *last_move)
{
	int		y;
	int		x;

	y = round(rc->cam->pos_y - rc->cam->dir_x / 15);
	x = round(rc->cam->pos_x + rc->cam->dir_y / 15);
	if (rc->world->map[y][x] != '1')
	{
		rc->cam->pos_y -= rc->cam->dir_x / 15;
		rc->cam->pos_x += rc->cam->dir_y / 15;
		get_time_ms(last_move);
	}
}

static void	move_backwards(t_raycaster *rc, unsigned int *last_move)
{
	int		y;
	int		x;

	y = round(rc->cam->pos_y - rc->cam->dir_y / 15);
	x = round(rc->cam->pos_x - rc->cam->dir_x / 15);
	if (rc->world->map[y][x] != '1')
	{
		rc->cam->pos_y -= rc->cam->dir_y / 15;
		rc->cam->pos_x -= rc->cam->dir_x / 15;
		get_time_ms(last_move);
	}
}

static void	move_right(t_raycaster *rc, unsigned int *last_move)
{
	int		y;
	int		x;

	y = round(rc->cam->pos_y + rc->cam->dir_x / 15);
	x = round(rc->cam->pos_x - rc->cam->dir_y / 15);
	if (rc->world->map[y][x] != '1')
	{
		rc->cam->pos_y += rc->cam->dir_x / 15;
		rc->cam->pos_x -= rc->cam->dir_y / 15;
		get_time_ms(last_move);
	}
}
