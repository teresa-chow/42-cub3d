/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:07 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/16 09:29:05 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	log_movement(int keycode, bool key_state[6]);
static void	log_rotation(int keycode, bool key_state[6]);

int	handle_keypress(int keycode, t_raycaster *rc)
{
	if (keycode == XK_Escape)
		close_quit(rc);
	log_movement(keycode, rc->key_state);
	log_rotation(keycode, rc->key_state);
	calc_player_movement(rc);
	return (0);
}

int	handle_keyrelease(int keycode, t_raycaster *rc)
{
	if (keycode == XK_w || keycode == XK_W)
		rc->key_state[0] = 0;
	else if (keycode == XK_a || keycode == XK_A)
		rc->key_state[1] = 0;
	else if (keycode == XK_s || keycode == XK_S)
		rc->key_state[2] = 0;
	else if (keycode == XK_d || keycode == XK_D)
		rc->key_state[3] = 0;
	if (keycode == XK_Left)
		rc->key_state[4] = 0;
	else if (keycode == XK_Right)
		rc->key_state[5] = 0;
	return (0);
}

static void	log_movement(int keycode, bool key_state[6])
{
	if (keycode == XK_w || keycode == XK_W || keycode == XK_a
		|| keycode == XK_A || keycode == XK_s || keycode == XK_S
		|| keycode == XK_d || keycode == XK_D)
	{
		key_state[0] = 0;
		key_state[1] = 0;
		key_state[2] = 0;
		key_state[3] = 0;
		if (keycode == XK_w || keycode == XK_W) // move forward
			key_state[0] = 1;
		else if (keycode == XK_a || keycode == XK_A) // move left
			key_state[1] = 1;
		else if (keycode == XK_s || keycode == XK_S) // move backwards
			key_state[2] = 1;
		else if (keycode == XK_d || keycode == XK_D) // move right
			key_state[3] = 1;
	}
}

static void	log_rotation(int keycode, bool key_state[6])
{
	if (keycode == XK_Left) // rotate left
	{
		key_state[4] = 1;
		key_state[5] = 0;
	}
	else if (keycode == XK_Right) // rotate right
	{
		key_state[4] = 0;
		key_state[5] = 1;
	}
}

int	close_quit(t_raycaster *rc)
{
	mlx_destroy_image(rc->img->mlx, rc->img->img);
	mlx_destroy_window(rc->img->mlx, rc->img->window);
	mlx_destroy_display(rc->img->mlx);
	free(rc->img->mlx);
    //free what's missing
	exit(EXIT_SUCCESS);
	return (0);
}