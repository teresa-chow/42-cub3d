/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:56:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/10 12:22:59 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

static void	init_mlx(t_data *img);


void render(t_world *world, t_raycaster *rc)
{
	/*t_world	test;
	test.tex_n = ;
	test.tex_s = ;
	test.tex_w = ;
	test.tex_e = ;
	test.ground = ;
	test.sky = ;
	test.map = malloc();*/

	rc->img = ft_calloc(1, sizeof(t_data));
	init_mlx(rc->img);
	//render_frame(world, rc);
	mlx_hook(rc->img->window, 2, 1L << 0, handle_keypress, rc);
	mlx_hook(rc->img->window, 17, 0L, close_quit, rc->img); //review argument
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
	img->addr = mlx_get_data_addr(img->img, &img->bits_pxl, \
		&img->line_len, &img->endian);
	return ;
}
