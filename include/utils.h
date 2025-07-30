/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:26:53 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:29:48 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parse.h"

/* ======================= DYNAMIC MEMORY MANAGEMENT ======================= */
void	free_world(t_world *world);
void	free_numbers(char **numbers);
void	free_map(char **map, int len);

/* ============================= ERROR HANDLING ============================ */
void	exit_file_analyze(t_world *world, int fd, char *msg, char *value);
void	printerr_exit(char *str, char *id);

#endif
