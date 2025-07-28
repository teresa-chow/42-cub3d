/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:41:55 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/25 17:27:30 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/render.h"

static void	init_vars(t_data *img, t_world *world, t_raycaster *raycaster);

int	main(int argc, char **argv)
{
	t_data	img;
	t_world	world;
	t_raycaster	rc;

	check_input(argc, argv[1]);
	init_vars(&img, &world, &rc);
	validate_map(argv[1], &world);
	// fill t_world world; create and fill t_camera *cam
	// launch_render_engine(&img, &world, &rc);
	//free world
	return (0);
}

static void	init_vars(t_data *img, t_world *world, t_raycaster *rc)
{
	ft_bzero(img, sizeof(t_data));
	ft_bzero(world, sizeof(t_world));
	ft_bzero(rc, sizeof(t_raycaster));
}
