/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:24:15 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/28 12:01:40 by tchow-so         ###   ########.fr       */
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

/*void	fill_textures(t_raycaster *rc, int x)
{
	void	*texture;
	int		y;

	y = rc->line_start;
	if (rc->cam->dir_y >= -1 && rc->cam->dir_y <= 0)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_n, &x, &y);
	else if (rc->cam->dir_y > 0 && rc->cam->dir_y <= 1)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_s, &x, &y);
	else if (rc->cam->dir_x > 0 && rc->cam->dir_x <= 1)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_e, &x, &y);
	else if (rc->cam->dir_x >= -1 && rc->cam->dir_x <= 0)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_w, &x, &y);
	while (y <= rc->line_end)
	{
		mlx_put_image_to_window(rc->img->mlx, rc->img->window, texture, 0, 0);
		y++;
	}
	if (rc->wall == EAST || rc->wall == WEST)
		rc->wall_x = rc->cam->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = rc->cam->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	//wall_x -= floor (?)
	if (rc->wall == NORTH)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_n, &x, &rc->line_start);
	else if (rc->wall == SOUTH)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_s, &x, &rc->line_start);
	else if (rc->wall == EAST)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_e, &x, &rc->line_start);
	else if (rc->wall == WEST)
		texture = mlx_xpm_file_to_image(rc->img->mlx, rc->world->tex_w, &x, &rc->line_start);
	mlx_put_image_to_window(rc->img->mlx, rc->img->window, texture, 0, 0);
}*/
