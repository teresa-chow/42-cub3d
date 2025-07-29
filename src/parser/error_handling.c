/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:20:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/29 21:08:57 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

void	exit_file_analyze(t_world *world, int fd, char *msg, char *value)
{
	free_world(world);
	if (fd)
		close(fd);
	printerr_exit(msg, value);
}

void	printerr_exit(char *str, char *value)
{
	int		len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	if (value)
		ft_putendl_fd(value, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
