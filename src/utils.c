/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:18:07 by sruff             #+#    #+#             */
/*   Updated: 2024/06/28 23:59:04 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(t_game *g, int index, int tx, int ty)
{
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[index], tx, ty);
}

int	load_map_two(t_game *g, char *map_str, int fd)
{
	if (map_str && *map_str)
		set_map(g, map_str);
	else
	{
		close(fd);
		free(map_str);
		return (exit_error(g, "Map is empty \n"), 0);
	}
	close(fd);
	return (1);
}

void	count_tiles_loop(t_game *g, t_tile_vars *t)
{
	while (t->y < g->map.y)
	{
		t->x = 0;
		while (t->x < g->map.x)
		{
			if (g->map.map_ptr[t->y][t->x] == 'P')
				t->start_counter++;
			else if (g->map.map_ptr[t->y][t->x] == 'E')
				t->exit_counter++;
			else if (g->map.map_ptr[t->y][t->x] == 'C')
			{
				g->collectables[t->collect_counter].x = t->x;
				g->collectables[t->collect_counter].y = t->y;
				t->collect_counter++;
			}
			else if (g->map.map_ptr[t->y][t->x] != '0' &&
				g->map.map_ptr[t->y][t->x] != '1')
				exit_error(g, "Map has invalid character");
			t->x++;
		}
		t->y++;
	}
}

int	flood_fill(t_game *g, int x, int y, int steps)
{
	if (x < 0 || x >= (int)g->map.x || y < 0 || y >= (int)g->map.y
		|| g->map.map_ptr[y][x] == '1' ||
	(g->map.visited[y][x] != '0' && g->map.visited[y][x] <= steps + '0'))
		return (0);
	if (g->map.visited[y][x] == '1' || g->map.map_ptr[y][x] == '1')
		return (0);
	g->map.visited[y][x] = steps + '1';
	flood_fill(g, x - 1, y, steps + 1);
	flood_fill(g, x + 1, y, steps + 1);
	flood_fill(g, x, y - 1, steps + 1);
	flood_fill(g, x, y + 1, steps + 1);
	return (0);
}
