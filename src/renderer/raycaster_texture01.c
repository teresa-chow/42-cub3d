/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:52:26 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 17:39:35 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static int	get_texel_color(int y, int x, t_texture tex);

/* Find where the wall's horizontal axis hits and scale it to texture width,
adjust mirroring for WEST and SOUTH textures */
int	map_wall_x_to_tex(t_raycaster *rc)
{
	t_texture	*texture;
	int			tex_x;

	texture = NULL;
	if (rc->wall == NORTH)
		texture = &rc->world->tex_north;
	else if (rc->wall == SOUTH)
		texture = &rc->world->tex_south;
	else if (rc->wall == EAST)
		texture = &rc->world->tex_east;
	else if (rc->wall == WEST)
		texture = &rc->world->tex_west;
	tex_x = (int)(rc->wall_x * (double)texture->width);
	if (tex_x == 0)
		tex_x = 1;
	if (rc->wall == WEST)
		tex_x = texture->width - tex_x;
	if (rc->wall == SOUTH)
		tex_x = texture->width - tex_x;
	return (tex_x);
}

/* texel - texture pixel */
int	get_texel(t_raycaster *rc, int y, int tex_x)
{
	int		color;

	color = 0;
	if (rc->wall == NORTH)
		color = get_texel_color(y, tex_x, rc->world->tex_north);
	else if (rc->wall == SOUTH)
		color = get_texel_color(y, tex_x, rc->world->tex_south);
	else if (rc->wall == EAST)
		color = get_texel_color(y, tex_x, rc->world->tex_east);
	else if (rc->wall == WEST)
		color = get_texel_color(y, tex_x, rc->world->tex_west);
	return (color);
}

static int	get_texel_color(int y, int tex_x, t_texture tex)
{
	char	*pos;
	int		color;

	color = 0;
	if ((tex_x > 0 && y > 0) && (tex_x < tex.width && y < tex.height))
	{
		pos = tex.data + (y * tex.line_len + tex_x * (tex.bits_pxl / 8));
		color = *(int *)pos;
	}
	return (color);
}
