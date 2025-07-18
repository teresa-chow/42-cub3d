/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:24:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/18 18:27:13 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/* Camera - player viewpoint (direction): */
/*
	NORTH : -Y pos_x = 0 pos_y = -1;
	SOUTH : +Y pos_x = 0 pos_y = +1;
	EAST : +X;
	WEST : -X;
*/

void	fill_textures(t_raycaster *rc, int x)
{
	void	*texture;
	int		y;

	y = rc->line_start;
	//if (rc->cam->dir_y >= -1 && rc->cam->dir_y <= 0)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_n, &x, &y);
	/*else if (rc->cam->dir_y > 0 && rc->cam->dir_y <= 1)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_s, &x, &y);
	else if (rc->cam->dir_x > 0 && rc->cam->dir_x <= 1)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_e, &x, &y);
	else if (rc->cam->dir_x >= -1 && rc->cam->dir_x <= 0)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_w, &x, &y);
	while (y <= rc->line_end)
	{*/
		mlx_put_image_to_window(rc->img->mlx, rc->img->window, texture, 0, 0);
	//	y++;
	//}
}
