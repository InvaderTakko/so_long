/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:03:15 by sruff             #+#    #+#             */
/*   Updated: 2024/06/16 18:46:51 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//check for valid characters
//check valid path
//find shortest path
//floodfill

// check if g->map.x is always the same = rectangle
int	check_rectangle(t_game *g)
{
	u_int32_t	x_len;
	u_int32_t	y;

	y = 0;
	x_len = g->map.x;
	while (y < g->map.y)
	{
		if (x_len != ft_strlen(g->map.map_ptr[y]))
			return (0);
		y++;
	}
	return (1);
}

int	count_tiles(t_game *g)
{
	u_int32_t	y;
	u_int32_t	x;
	int	start_counter;
	int	exit_counter;
	int	collect_counter;

	y = 0;
	x = 0;
	start_counter = 0;
	exit_counter = 0;
	collect_counter = 0;
	while (y < g->map.y)
	{
		x = 0;
		while (x < g->map.x)
		{
			if (g->map.map_ptr[y][x] == 'P')
				start_counter++;
			else if (g->map.map_ptr[y][x] == 'E')
				exit_counter++;
			else if (g->map.map_ptr[y][x] == 'C')
				collect_counter++;
			else if (g->map.map_ptr[y][x]  != '0' && g->map.map_ptr[y][x]  != '1' )
				return (0);
			x++;
		}
		y++;
	}
	g->map.amount_collectibles = collect_counter;
	if (start_counter != 1 || exit_counter != 1 || collect_counter < 1)
		return (0);
	else
		return (1);
}

int collect_reachable(t_game *g)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < g->map.y)
	{
		x = 0;
		while (x < g->map.x)
		{
			// ft_printf("map: %c\n visited: %c\n",g->map.map_ptr[y][x], g->map.visited[y][x]);
			if (g->map.visited[y][x] != '1' && g->map.map_ptr[y][x] == 'C')
				return (0);
			x++;	
		}
		y++;
	}
	return (1);
}
int flood_fill(t_game *g, int x, int y) // add input to differentiate between map validity check on start or for use of only finding shortest path
{
	ft_printf("floodfill x: %d y: %d visited : %c\n", x, y, g->map.visited[y][x]);
    if (x >= (int)g->map.x || y >= (int)g->map.y || x < 0 || y < 0)
        return (0);
	if (g->map.visited[y][x] == '1' || g->map.map_ptr[y][x] == '1')
		return 0;
    // if (g->map.map_ptr[y][x] == 'P')
    //     return (1);
	// ft_printf("do i get here \n");
    if (g->map.map_ptr[y][x] == 'C')
        g->player.collected++;
    g->map.visited[y][x] = '1'; //path of 1s is the correct one. after all coins collected check map_ptr[x][y]/visited[x][y] if im only on 1(visited)
    // if (flood_fill(g, x - 1, y)) // check if valid
    //     return (1);
    // if (flood_fill(g, x + 1, y)) // check if valid
    //     return (1);
    // if (flood_fill(g, x , y - 1)) // check if valid
    //     return (1);
    // if (flood_fill(g, x , y + 1)) // check if valid
    //     return (1);
	flood_fill(g, x - 1, y);
    flood_fill(g, x + 1, y);
	flood_fill(g, x , y - 1);
	flood_fill(g, x , y + 1);
    // g->map.visited[y][x] = '0';
    if (g->map.map_ptr[y][x] == 'C')
        g->player.collected--;
    return (0);
}
// checks if valid path exists tracks if it collects something

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

	ft_printf("\n");
	ft_printf("\n");
	i = 0;
	j = 0;
	while (i < g->map.y)
	{
		while (j < g->map.x)
		{
			ft_printf("%c", g->map.map_ptr[i][j]);
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






