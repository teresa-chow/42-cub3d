/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:07 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/10 14:37:07 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	log_movement(int keycode, bool key_state[6]);
static void	log_rotation(int keycode, bool key_state[6]);

//triggers callback once per event
int	handle_keypress(int keycode, t_raycaster *rc)
{
	if (keycode == XK_Escape)
		close_quit(rc->img); //review argument
	log_movement(keycode, rc->key_state);
	log_rotation(keycode, rc->key_state);
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

int	close_quit(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->window);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
    //free what's missing
	exit(EXIT_SUCCESS);
	return (0);
}