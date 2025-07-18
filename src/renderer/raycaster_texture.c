/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:24:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/18 15:38:58 by tchow-so         ###   ########.fr       */
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

/*void    fill_textures(t_raycaster *rc)
{
    void    *north;
    void    *south;
    void    *east;
    void    *west;

    north = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_n, *width, *height);
    south = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_s, *width, *height);
    east = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_e, *width, *height);
    west = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_w, *width, *height);
    mlx_put_image_to_window(rc->img->mlx, rc->img->window, north, 0, 0);
}*/