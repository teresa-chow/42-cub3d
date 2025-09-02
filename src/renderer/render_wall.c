/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:13:29 by tchow-so          #+#    #+#             */
/*   Updated: 2025/09/02 12:29:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	init_texel(t_raycaster *rc, t_texel_info *texel);

void	draw_vertical_line(t_raycaster *rc, int x)
{
	int				y;
	int				color;
	t_texel_info	texel;

	ft_bzero(&texel, sizeof(t_texel_info));
	init_texel(rc, &texel);
	texel.tex_x = map_wall_x_to_tex(rc);
	texel.step = 1.0 * texel.texture->height / rc->line_height;
	texel.tex_pos = (rc->line_start - WIN_H / 2 + rc->line_height / 2)
		* texel.step;
	y = rc->line_start;
	while (y < rc->line_end)
	{
		texel.tex_y = (int)texel.tex_pos & (texel.texture->height - 1);
		if (texel.tex_y == 0)
			texel.tex_y = 1;
		texel.tex_pos += texel.step;
		color = get_texel(rc, texel.tex_y, texel.tex_x);
		pixel_put(rc->img, x, y, color);
		y++;
	}
}

static void	init_texel(t_raycaster *rc, t_texel_info *texel)
{
	texel->tex_x = 0;
	texel->tex_y = 0;
	texel->tex_pos = 0;
	texel->step = 0;
	if (rc->wall == NORTH)
		texel->texture = &rc->world->tex_south;
	else if (rc->wall == SOUTH)
		texel->texture = &rc->world->tex_north;
	else if (rc->wall == EAST)
		texel->texture = &rc->world->tex_west;
	else if (rc->wall == WEST)
		texel->texture = &rc->world->tex_east;
}
