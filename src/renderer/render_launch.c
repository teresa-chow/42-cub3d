/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:56:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/18 16:57:32 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	tmp_fill_values(t_raycaster *rc); //placeholder

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
		printerr_exit("Failed to initialize MLX\n");
	img->window = mlx_new_window(img->mlx, WIN_W, WIN_H, "cub3D");
	if (img->window == NULL)
	{
		free(img->mlx);
		printerr_exit("Failed to open window\n");
	}
	img->img = mlx_new_image(img->mlx, WIN_W, WIN_H);
	if (img->img == NULL)
	{
		free(img->window);
		free(img->mlx);
		printerr_exit("Failed to create new image\n");
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
	world->cam = malloc(sizeof(t_camera)); //tmp
	rc->cam = world->cam;
	tmp_fill_values(rc); //tmp
	rc->plane_x = -rc->cam->dir_y * 0.66;
	rc->plane_y = rc->cam->dir_x * 0.66;
	/*if (rc->cam->dir_x == 0)
		rc->plane_x = 0.66;
	else if (rc->cam->dir_y == 0)
		rc->plane_y = 0.66;*/
}

// TODO: delete code block
/* tmp values for test: these values will already be filled in parsing stage */
static void	tmp_fill_values(t_raycaster *rc)
{
	rc->cam->pos_x = 22;
	rc->cam->pos_y = 12;
	/* ratio between length of dir and cam_plane determines FOV,
	these values will change but keep length and perpendicularity */
	rc->cam->dir_x = -1;
	rc->cam->dir_y = 0;
	rc->world->map = ft_calloc(25, sizeof(char *));
	char	*map[] = {"111111111111111111111111", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000011111000000001", "100000000000001000000001",
		"10000N000010001000000001", "100000000000001000000001",
		"100000000010001000000001", "100000000000001000000001",
		"100000000010001000000001", "100000000000001000000001",
		"100000000011011000000001", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "111111111111111111111111"
	};
	rc->world->map_wid = 24;
	rc->world->map_len = 24;
	rc->world->tex_n = ft_strdup("assets/textures/birds_tex_n.xpm");
	rc->world->tex_s = ft_strdup("assets/textures/birds_tex_s.xpm");
	rc->world->tex_w = ft_strdup("assets/textures/birds_tex_w.xpm");
	rc->world->tex_e = ft_strdup("assets/textures/birds_tex_e.xpm");
	rc->world->sky = 65535;
	rc->world->ground = 255;
	for (int j = 0; j < rc->world->map_len; j++)
		rc->world->map[j] = ft_strdup(map[j]);
}
