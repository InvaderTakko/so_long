/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:14:13 by sruff             #+#    #+#             */
/*   Updated: 2024/06/24 22:52:03 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_collected(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->map.amount_collectibles)
	{
		if (g->collectables[i].x == x && g->collectables[i].y == y)
		{
			if (!g->collectables[i].collected)
			{
				g->collectables[i].collected = 1;
				g->player.collected++;
			}
		}
		i++;
	}
}

void	check_next_tile(t_game *g, int x, int y)
{
	if (g->map.map_ptr[y][x] == '0' || g->map.map_ptr[y][x] == 'P' ||
		g->map.map_ptr[y][x] == 'E' || g->map.map_ptr[y][x] == 'C')
	{
		if (g->player.collected == g->map.amount_collectibles)
		{
			if (g->map.visited[y][x] != g->map.prev - 1)
				ft_printf("learn to play \n");
		}
		g->player.x = x;
		g->player.y = y;
		g->player.steps++;
		render_steps(g);
		if (g->map.map_ptr[y][x] == 'C')
			check_collected(g, x, y);
		if (g->player.collected == g->map.amount_collectibles
			&& g->map.map_ptr[y][x] == 'E')
		{
			ft_printf("You won in %d steps!\n", g->player.steps); // fix exit
			cleanup_game(g);
			exit(EXIT_SUCCESS);
		}
		g->map.prev = g->map.visited[y][x];
	}
	ft_printf("Steps: %d\n", g->player.steps);
}
