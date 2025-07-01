/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:41:55 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/01 12:23:20 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	img; //mlx info


	check_input(argc, argv[1]);
	ft_bzero(&img, sizeof(img));
	//validate map
	new_img(&img);
	//new img + rendering loop
	//free map
	return (0);
}
