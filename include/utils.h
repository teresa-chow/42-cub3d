/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:26:53 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/01 16:36:50 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parse.h"

typedef enum e_err_code
{
	MEMALLOC,
	INPUT_ARGC,
	INPUT_FORMAT,
	CONFIG_OPEN,
	SPEC_INVALID,
	SPEC_REPEATED,
	SPEC_UNEXPECTED,
	COLOR_RGB,
	COLOR_INVALID,
	COLOR_MISSING,
	TEX_FORMAT,
	TEX_PATH,
	TEX_MISSING,
	MAP_EXTRA,
	PLAYER_POS_INVALID,
	PLAYER_POS_EXTRA,
	PLAYER_POS_NONE,
	MAP_OPEN,
	MAP_INVALID,
	MLX_INIT,
	MLX_WIN,
	MLX_IMG
}	t_err_code;

/* ======================= DYNAMIC MEMORY MANAGEMENT ======================= */
void	free_world(t_world *world);
void	free_numbers(char **numbers);
void	free_map(char **map, int len);

/* ============================= ERROR HANDLING ============================ */
void	exit_on_error(t_world *world, int fd, t_err_code err, t_tmp *tmp);
void	print_error(t_err_code err);

#endif
