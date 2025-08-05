/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 00:53:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

/* ============================== RENDERING ================================ */
// Rendering
void	launch_render_engine_bonus(t_data *img, t_world *world,
			t_raycaster *rc);
int		render_frame_bonus(t_raycaster *rc);
void	draw_minimap(t_raycaster *rc);
void	draw_minimap_grid(t_raycaster *rc, t_dda *dda);
void	draw_player(t_raycaster *rc, float spacing);

#endif
