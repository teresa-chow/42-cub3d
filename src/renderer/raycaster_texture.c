/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:24:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:15:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	tex_xpm_to_img(t_raycaster *rc);
static void	tex_get_img_data(t_raycaster *rc);

void	init_textures(t_raycaster *rc)
{
	tex_xpm_to_img(rc);
	tex_get_img_data(rc);
}

static void	tex_xpm_to_img(t_raycaster *rc)
{
	rc->world->tex_north.img = mlx_xpm_file_to_image(rc->img->mlx,
		rc->world->tex_n, &rc->world->tex_north.width,
		&rc->world->tex_north.height);
	rc->world->tex_south.img = mlx_xpm_file_to_image(rc->img->mlx,
		rc->world->tex_s, &rc->world->tex_south.width,
		&rc->world->tex_south.height);
	rc->world->tex_east.img = mlx_xpm_file_to_image(rc->img->mlx,
		rc->world->tex_e, &rc->world->tex_east.width,
		&rc->world->tex_east.height);
	rc->world->tex_west.img = mlx_xpm_file_to_image(rc->img->mlx,
		rc->world->tex_w, &rc->world->tex_west.width,
		&rc->world->tex_west.height);
}

static void	tex_get_img_data(t_raycaster *rc)
{
	rc->world->tex_north.data = mlx_get_data_addr(rc->world->tex_north.img,
		&rc->world->tex_north.bits_pxl, &rc->world->tex_north.line_len,
		&rc->world->tex_north.endian);
	rc->world->tex_south.data = mlx_get_data_addr(rc->world->tex_south.img,
		&rc->world->tex_south.bits_pxl, &rc->world->tex_south.line_len,
		&rc->world->tex_south.endian);
	rc->world->tex_east.data = mlx_get_data_addr(rc->world->tex_east.img,
		&rc->world->tex_east.bits_pxl, &rc->world->tex_east.line_len,
		&rc->world->tex_east.endian);
	rc->world->tex_west.data = mlx_get_data_addr(rc->world->tex_west.img,
		&rc->world->tex_west.bits_pxl, &rc->world->tex_west.line_len,
		&rc->world->tex_west.endian);
}
