/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_minimap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:47:37 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 10:29:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/render_bonus.h"
#include "../../include/utils.h"

/* Check minimap dimension */
void	check_minimap(t_raycaster *rc, t_dda dda)
{
	if (rc->world->map_wid * dda.spacing > WIN_W / 5
		|| rc->world->map_len * dda.spacing > WIN_H / 4)
	{
		mlx_destroy_image(rc->img->mlx, rc->world->tex_north.img);
		mlx_destroy_image(rc->img->mlx, rc->world->tex_south.img);
		mlx_destroy_image(rc->img->mlx, rc->world->tex_west.img);
		mlx_destroy_image(rc->img->mlx, rc->world->tex_east.img);
		mlx_destroy_image(rc->img->mlx, rc->img->img);
		mlx_destroy_window(rc->img->mlx, rc->img->window);
		mlx_destroy_display(rc->img->mlx);
		free(rc->img->mlx);
		free_world(rc->world);
		print_error(MINIMAP_SIZE);
		exit(EXIT_FAILURE);
	}
}
