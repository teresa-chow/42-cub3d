/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:20:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/04 23:07:52 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	exit_on_error(t_world *world, int fd, t_err_code err, t_tmp *tmp)
{
	free_world(world);
	if (tmp)
	{
		free(tmp->to_free);
		free(tmp->line);
		if (tmp->map_cpy)
			free_map(tmp->map_cpy, world->map_len);
	}
	if (fd != -1 && fd != 0)
		close(fd);
	print_error(err);
	exit(EXIT_FAILURE);
}
