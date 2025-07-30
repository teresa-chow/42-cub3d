/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:56:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:00:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	init_mlx(t_data *img);
static void	init_raycaster(t_world *world, t_raycaster *rc, t_data *img);

void	launch_render_engine(t_data *img, t_world *world, t_raycaster *rc)
{
	init_mlx(img);
	init_raycaster(world, rc, img);
	mlx_loop_hook(rc->img->mlx, render_frame, rc);
	mlx_hook(rc->img->window, 2, 1L << 0, handle_keypress, rc);
	mlx_hook(rc->img->window, 3, 1L << 1, handle_keyrelease, rc);
	mlx_hook(rc->img->window, 17, 0L, close_quit, rc);
	mlx_loop(rc->img->mlx);
}

static void	init_mlx(t_data *img)
{
	img->mlx = mlx_init();
	if (img->mlx == NULL)
		printerr_exit("Failed to initialize MLX\n", NULL);
	img->window = mlx_new_window(img->mlx, WIN_W, WIN_H, "cub3D");
	if (img->window == NULL)
	{
		free(img->mlx);
		printerr_exit("Failed to open window\n", NULL);
	}
	img->img = mlx_new_image(img->mlx, WIN_W, WIN_H);
	if (img->img == NULL)
	{
		free(img->window);
		free(img->mlx);
		printerr_exit("Failed to create new image\n", NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_pxl,
			&img->line_len, &img->endian);
	return ;
}

/* Field of View (FOV) is set to 66 degrees,
adequate for First-Person Shooter (FPS) */
static void	init_raycaster(t_world *world, t_raycaster *rc, t_data *img)
{
	rc->img = img;
	get_time_ms(&rc->curr_time_ms);
	rc->prev_time_ms = rc->curr_time_ms;
	rc->world = world;
	rc->cam = world->cam;
	rc->plane_x = -rc->cam->dir_y * 0.66;
	rc->plane_y = rc->cam->dir_x * 0.66;
	init_textures(rc);
	/*if (rc->cam->dir_x == 0)
		rc->plane_x = 0.66;
	else if (rc->cam->dir_y == 0)
		rc->plane_y = 0.66;*/
}
