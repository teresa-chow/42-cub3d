/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:07 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/01 12:25:29 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_keypress(int keycode, t_data *img)
{
	if (keycode == XK_Escape)
		close_quit(img);
	return (0);
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