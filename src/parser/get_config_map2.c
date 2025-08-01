/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_map2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:23:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/01 16:32:09 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	zero_player_pos_map(t_world *world)
{
	int		y;
	int		x;

	y = 0;
	while (y < world->map_len)
	{
		x = 0;
		while (world->map[y][x])
		{
			if (world->map[y][x] == 'N' || world->map[y][x] == 'S'
			|| world->map[y][x] == 'E' || world->map[y][x] == 'W')
				world->map[y][x] = '0';
			x++;
		}
		y++;
	}
}
