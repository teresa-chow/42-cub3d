/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:04:49 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/18 08:33:06 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

/* Get time of day to calculate movement cooldown */
void	get_time_ms(unsigned int *curr_time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	*curr_time = now.tv_sec * 1e3 + now.tv_usec / 1e3;
}
