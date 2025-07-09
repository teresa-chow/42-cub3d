/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:07 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/09 14:41:42 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	handle_movement(int keycode);
static void	handle_rotation(int keycode);

//triggers callback once per event
int	handle_keypress(int keycode, t_data *img)
{
	if (keycode == XK_Escape)
		close_quit(img);
	handle_movement(keycode);
	handle_rotation(keycode);
	return (0);
}

static void	handle_movement(int keycode)
{
	if (keycode == XK_w || keycode == XK_W)
	/* move forward */printf("W\n");
	else if (keycode == XK_s || keycode == XK_S)
	/* move backwards */printf("S\n");
	else if (keycode == XK_a || keycode == XK_A)
	/* move left */printf("A\n");
	else if (keycode == XK_d || keycode == XK_D)
	/* move right */printf("D\n");
}

static void	handle_rotation(int keycode)
{
	if (keycode == XK_Right)
	/* rotate right */printf("R\n");
	else if (keycode == XK_Left)
	/* rotate left */printf("L\n");
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