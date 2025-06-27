/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:56:00 by tchow-so          #+#    #+#             */
/*   Updated: 2025/06/27 15:59:30 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_mlx(t_data *img);

void	new_img(t_data *img)
{
	init_mlx(img);
	render_img(img);
	mlx_hook(img->window, 2, 1L << 0, handle_keypress, img);
	mlx_hook(img->window, 17, 0L, close_quit, img);
	mlx_loop(img->mlx);
}

static void	init_mlx(t_data *img)
{
	img->mlx = mlx_init();
	if (img->mlx == NULL)
		printerr_exit("Failed to initialize MLX\n");
	img->window = mlx_new_window(img->mlx, WIN_W, WIN_H, "FDF");
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