/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_tex_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:48:06 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/29 21:18:55 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

/* Check that all textures are set up */
int	all_textures_set_up(t_world *world)
{
	if (world->tex_n && world->tex_s && world->tex_e
		&& world->tex_w && world->sky_str && world->ground_str)
		return (1);
	return (0);
}

/* Find value to identifier */
void	find_identifier_value(char *s, t_world *world, int fd, char *value)
{
	while (*s)
	{
		if (!ft_isspace(*s))
			return ;
		s++;
	}
	exit_file_analyze(world, fd, "Error\n"
		"Missing value for identifier: ", value);
}
