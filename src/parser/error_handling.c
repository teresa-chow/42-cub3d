/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:20:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/25 16:24:41 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void    exit_file_analyze(t_world *world, int fd, char *msg)
{
		free_world(world);
		close(fd);
		printerr_exit(msg);
}

void	printerr_exit(char *str)
{
	int		len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	exit(EXIT_FAILURE);
}
