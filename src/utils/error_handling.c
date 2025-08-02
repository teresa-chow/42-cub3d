/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:20:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/01 16:35:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	exit_on_error(t_world *world, int fd, t_err_code err, t_tmp *tmp)
{
	free_world(world);
	free(tmp->to_free); //add
	free(tmp->line);
	if (tmp->map_cpy)
		free_map(tmp->map_cpy, world->map_len);
	close(fd);
	print_error(err);
	exit(EXIT_FAILURE);
}
