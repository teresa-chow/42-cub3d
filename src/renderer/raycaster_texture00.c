/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:24:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 13:53:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/utils.h"

static void	tex_xpm_to_img(t_raycaster *rc);
static void	check_xpm_file(t_raycaster *rc);
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
	check_xpm_file(rc);
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

static void	check_xpm_file(t_raycaster *rc)
{
	if (!rc->world->tex_north.img || !rc->world->tex_south.img
		|| !rc->world->tex_east.img || !rc->world->tex_west.img)
	{
		if (rc->world->tex_north.img)
			mlx_destroy_image(rc->img->mlx, rc->world->tex_north.img);
		if (rc->world->tex_south.img)
			mlx_destroy_image(rc->img->mlx, rc->world->tex_south.img);
		if (rc->world->tex_west.img)
			mlx_destroy_image(rc->img->mlx, rc->world->tex_west.img);
		if (rc->world->tex_east.img)
			mlx_destroy_image(rc->img->mlx, rc->world->tex_east.img);
		mlx_destroy_image(rc->img->mlx, rc->img->img);
		mlx_destroy_window(rc->img->mlx, rc->img->window);
		mlx_destroy_display(rc->img->mlx);
		free(rc->img->mlx);
		free_world(rc->world);
		print_error(MLX_XPM);
		exit(EXIT_FAILURE);
	}
}
