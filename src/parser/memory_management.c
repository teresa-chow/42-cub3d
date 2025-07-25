/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:26:27 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/25 16:27:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	free_world(t_world *world)
{
	free(world->tex_e);
	free(world->tex_w);
	free(world->tex_s);
	free(world->tex_n);
	free(world->ground_str);
	free(world->sky_str);
}
