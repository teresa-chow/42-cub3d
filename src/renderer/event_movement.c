/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:40:43 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/16 12:13:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

void    calc_player_movement(t_raycaster *rc)
{
    int y;
    int x;

    y = (int)rc->cam->pos_y;
    x = (int)rc->cam->pos_x;
    if (rc->world->map[y - 1][x] != '1' && rc->key_state[0] == 1)
        rc->cam->pos_y -= 1;
    else if (rc->world->map[y][x - 1] != '1' && rc->key_state[1] == 1)
        rc->cam->pos_x -= 1;
    else if (rc->world->map[y + 1][x] != '1' && rc->key_state[2] == 1)
        rc->cam->pos_y += 1;
    else if (rc->world->map[y][x + 1] != '1' && rc->key_state[3] == 1)
        rc->cam->pos_x += 1;
}

/*void    calc_player_rotation(t_raycaster *rc)
{
    
}*/