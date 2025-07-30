/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:26:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:31:22 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	free_world(t_world *world)
{
	free(world->tex_n);
	free(world->tex_s);
	free(world->tex_e);
	free(world->tex_w);
	free(world->ground_str);
	free(world->sky_str);
	free(world->cam);
	if (world->map_cpy)
		free_map(world->map_cpy, world->map_len);
	if (world->map)
		free_map(world->map, world->map_len);
}

void	free_map(char **map, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(map[i]);
	free(map);
}

void	free_numbers(char **numbers)
{
	int	i;

	i = -1;
	while (numbers[++i])
		free(numbers[i]);
	free(numbers);
}
