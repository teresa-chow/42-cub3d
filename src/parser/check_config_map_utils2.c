/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:34:07 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/29 15:35:02 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static void	remove_new_line(t_world *world);

void	format_map_lines(t_world *world)
{
	int	i;
	int	j;
	char	**map;

	i = -1;
	j = -1;
	map = world->map;
	while (++i < world->map_len)
	{
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' 
			|| map[i][j] == 'E' || map[i][j] == 'W')
				map[i][j] = '0';
			
		}
		j = -1;
	}
	remove_new_line(world);
}

static void	remove_new_line(t_world *world)
{
	int	i;
	int	len;
	char	**map;
	char	*new;

	i = -1;
	map = world->map;
	while (++i < world->map_len)
	{
		if (ft_strchr(map[i], '\n'))
		{
			len = ft_strlen(map[i]) - ft_strlen(ft_strchr(map[i], '\n'));
			new = ft_substr(map[i], 0, len);
			if (!new)
				exit_file_analyze(world, 0, "Error\nMemory allocation\n", NULL);
			free(map[i]);
			map[i] = new;
		}			
	}
}
