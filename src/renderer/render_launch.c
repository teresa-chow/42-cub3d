/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:56:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 09:44:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"
#include "../../include/utils.h"

static void	init_mlx(t_data *img, t_world *world);
static void	init_mlx_img(t_data *img, t_world *world);
static void	init_raycaster(t_world *world, t_raycaster *rc, t_data *img);

void	launch_render_engine(t_data *img, t_world *world, t_raycaster *rc)
{
	init_mlx(img, world);
	init_raycaster(world, rc, img);
	mlx_loop_hook(rc->img->mlx, render_frame, rc);
	mlx_hook(rc->img->window, 2, 1L << 0, handle_keypress, rc);
	mlx_hook(rc->img->window, 3, 1L << 1, handle_keyrelease, rc);
	mlx_hook(rc->img->window, 17, 0L, close_quit, rc);
	mlx_loop(rc->img->mlx);
}

static void	init_mlx(t_data *img, t_world *world)
{
	img->mlx = mlx_init();
	if (img->mlx == NULL)
	{
		free_world(world);
		print_error(MLX_INIT);
		exit(EXIT_FAILURE);
	}
	img->window = mlx_new_window(img->mlx, WIN_W, WIN_H, "cub3D");
	if (img->window == NULL)
	{
		free(img->mlx);
		free_world(world);
		print_error(MLX_WIN);
		exit(EXIT_FAILURE);
	}
	init_mlx_img(img, world);
	return ;
}

static void	init_mlx_img(t_data *img, t_world *world)
{
	img->img = mlx_new_image(img->mlx, WIN_W, WIN_H);
	if (img->img == NULL)
	{
		free(img->window);
		free(img->mlx);
		free_world(world);
		print_error(MLX_IMG);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_pxl,
			&img->line_len, &img->endian);
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
	if (rc->cam->dir_x == 0)
		rc->plane_x = 0.66;
	else if (rc->cam->dir_y == 0)
		rc->plane_y = 0.66;
	init_textures(rc);
}
