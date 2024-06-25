/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:03:15 by sruff             #+#    #+#             */
/*   Updated: 2024/06/25 14:06:07 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(t_game *g)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	while (x < g->map.x)
	{
		if (g->map.map_ptr[0][x] != '1' ||
		g->map.map_ptr[g->map.y - 1][x] != '1')
			exit_error(g, "map not sourrounded by walls");
		x++;
	}
	while (y < g->map.y)
	{
		if (g->map.map_ptr[y][0] != '1' ||
		g->map.map_ptr[y][g->map.x - 1] != '1')
			exit_error(g, "map not sourrounded by walls");
		y++;
	}
	return (1);
}

int	check_rectangle(t_game *g)
{
	int32_t	x_len;
	int32_t	y;

	y = 0;
	x_len = g->map.x;
	while (y < g->map.y)
	{
		if (x_len != (int32_t)ft_strlen(g->map.map_ptr[y]))
			exit_error(g, "map not rectangular");
		y++;
	}
	return (1);
}

int	count_tiles(t_game *g)
{
	t_tile_vars	t;

	ft_memset(&t, 0, sizeof(t_tile_vars));
	count_tiles_loop(g, &t);
	if (t.start_counter != 1 || t.exit_counter != 1 || t.collect_counter < 1)
		return (exit_error(g, "map has too few/many P/E/C tiles"), 0);
	else
		return (1);
}

int	collect_reachable(t_game *g)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < g->map.y)
	{
		x = 0;
		while (x < g->map.x)
		{
			if (g->map.visited[y][x] == '0' && g->map.map_ptr[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	create_visited(t_game *g)
{
	char	**visited;
	int32_t	i;
	int32_t	j;

	i = 0;
	j = 0;
	visited = (char **)ft_calloc(g->map.y + 1, sizeof(char *));
	while (i < g->map.y)
	{
		visited[i] = (char *)ft_calloc(g->map.x + 1, sizeof(char));
		while (j < g->map.x)
		{
			visited[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
	g->map.visited = visited;
	visited = NULL;
	g->player.collected = 0;
	flood_fill(g, g->map.exit_x, g->map.exit_y, 0);
}

	// i = 0;
	// j = 0;
	// while (i < g->map.y)
	// {
	// 	while (j < g->map.x)
	// 	{
	// 		ft_printf("%c", g->map.visited[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	j = 0;
	// 	// ft_printf("X bool: %d\n",i + 1);
	// 	i++;
	// }

	// ft_printf("\n");
	// ft_printf("\n");
	// i = 0;
	// j = 0;
	// while (i < g->map.y)
	// {
	// 	while (j < g->map.x)
	// 	{
	// 		ft_printf("%c", g->map.map_ptr[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	j = 0;
	// 	// ft_printf("X bool: %d\n",i + 1);
	// 	i++;
	// }