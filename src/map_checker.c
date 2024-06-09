/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:03:15 by sruff             #+#    #+#             */
/*   Updated: 2024/06/09 20:01:49 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//check for valid characters
//check valid path
//find shortest path
//floodfill


int flood_fill(t_game *g, int x, int y) // add input to differentiate between map validity check on start or for use of only finding shortest path
{
	ft_printf("floodfill x: %d y: %d visited : %c\n", x, y, g->map.visited[y][x]);
    if (x >= (int)g->map.x || y >= (int)g->map.y || x < 0 || y < 0)
        return (0);
	if (g->map.visited[y][x] == '1' || g->map.map_ptr[y][x] == '1')
		return 0;
    if (g->map.map_ptr[y][x] == 'P')
        return (1);
	// ft_printf("do i get here \n");
    if (g->map.map_ptr[y][x] == 'C')
        g->player.collected++;
    g->map.visited[y][x] = '1'; //path of 1s is the correct one. after all coins collected check map_ptr[x][y]/visited[x][y] if im only on 1(visited)
    if (flood_fill(g, x - 1, y)) // check if valid
        return (1);
    if (flood_fill(g, x + 1, y)) // check if valid
        return (1);
    if (flood_fill(g, x , y - 1)) // check if valid
        return (1);
    if (flood_fill(g, x , y + 1)) // check if valid
        return (1);
	// flood_fill(g, x - 1, y);
    // flood_fill(g, x + 1, y);
	// flood_fill(g, x , y - 1);
	// flood_fill(g, x , y + 1);
    g->map.visited[y][x] = '0';
    if (g->map.map_ptr[y][x] == 'C')
        g->player.collected--;
    return (0);
}

//if g->player.collected != g->map.amount_collectibles = cant collect all of them ERROR

//create bool visited** same lenght copy of char **map and set bool[i][j] = false (unvisited)
//throw visited** and map** into floodfill

void	create_visited(t_game *g)
{
	char	**visited;
	u_int32_t	i;
	u_int32_t	 j;
	int			game_beatable;

	i = 0;
	j = 0;
	visited = (char **)ft_calloc(g->map.y + 1, sizeof(char *));
	while (i < g->map.y)
	{
		visited[i] = (char *)ft_calloc(g->map.x + 1, sizeof(char));
		while (j < g->map.x)
		{
			// ft_printf("Y bool : %d\n", j + 1);
			visited[i][j] = '0';
			j++;
		}
		j = 0;
		// ft_printf("X bool: %d\n",i + 1);
		i++;
	}
	g->map.visited = visited;
	visited = NULL;
	g->player.collected = 0;
	game_beatable = flood_fill(g, g->map.exit_x, g->map.exit_y);
	i = 0;
	j = 0;
	while (i < g->map.y)
	{
		while (j < g->map.x)
		{
			ft_printf("%c", g->map.visited[i][j]);
			j++;
		}
		ft_printf("\n");
		j = 0;
		// ft_printf("X bool: %d\n",i + 1);
		i++;
	}
	ft_printf("collectable on map: %d\n collected: %d\n", g->map.amount_collectibles, g->player.collected);
	//if g->player.collected != g->map.amount_collectibles = cant collect all of them -> game_beatable = 0
}






