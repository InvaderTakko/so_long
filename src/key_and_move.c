/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:14:13 by sruff             #+#    #+#             */
/*   Updated: 2024/06/09 15:20:23 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_next_tile(t_game *g, int x, int y)
{
	if (g->map.map_ptr[y][x] == '1')
	{
		// g->player.steps++;
		//increase nothing
	}	
	else if (g->map.map_ptr[y][x] == '0' || g->map.map_ptr[y][x] == 'P')
	{
		g->player.x = x;
		g->player.y = y;
		g->player.steps++;
		//increase steps
	}
	else if (g->map.map_ptr[y][x] == 'C')
	{
		g->player.x = x;
		g->player.y = y;
		g->player.steps++;
		//increase steps and collect counter
		//start
	}
	else if (g->map.map_ptr[y][x] == 'E')
	{
		g->player.steps++;
		//succes
	}
	ft_printf("Steps: %d\n", g->player.steps);

}