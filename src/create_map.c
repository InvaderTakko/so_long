/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:47:28 by sruff             #+#    #+#             */
/*   Updated: 2024/06/24 22:48:51 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


static void	load_tile(t_game *g, char c, int x, int y)
{

	if (c == '0')
		load_image(g, 0, x * TILE, y * TILE);
	else if (c == '1')
		load_image(g, 2, x * TILE, y * TILE);
	else if (c == 'E')
	{
		load_image(g, 3, x * TILE, y * TILE);
		g->map.exit_x = x;
		g->map.exit_y = y;
	}
	else if (c == 'P')
	{
		load_image(g, 1, x * TILE, y * TILE);
		g->player.x = x;
		g->player.y = y;
	}
	else if (c == 'C')
	{
		load_image(g, 0, x * TILE, y * TILE);
		load_image(g, 4, x * TILE, y * TILE);
		g->map.amount_collectibles++;
	}
}

static void	load_pngs(t_game *g)
{
	int	i;

	i = 0;
	(g->text.texture)[0] = mlx_load_png(IMG_TILE);
	(g->text.texture)[1] = mlx_load_png(IMG_PLAYER);
	(g->text.texture)[2] = mlx_load_png(IMG_WALL);
	(g->text.texture)[3] = mlx_load_png(IMG_GOAL);
	(g->text.texture)[4] = mlx_load_png(IMG_COLLECT);
	while (i <= 4)
	{
		(g->text.img)[i] = mlx_texture_to_image(g->mlx_ptr,
				(g->text.texture)[i]);
		mlx_resize_image((g->text.img)[i], TILE, TILE);
		i++;
	}
}

static void	spawn_objects(t_game *g)
{
	int32_t	x;
	int32_t	y;
	char	**map;
	char	c;

	x = 0;
	y = 0;
	map = g->map.map_ptr;
	load_pngs(g);
	while (y < g->map.y)
	{
		while (x <= g->map.x - 1)
		{
			c = map[y][x];
			load_tile(g, c, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	set_map(t_game *g, char *map_str)
{
	char		**temp;
	int			len;
	t_window	window;

	len = 0;
	ft_memset(&window, 0, sizeof(t_window));
	g->map.map_ptr = ft_split(map_str, '\n');
	free(map_str);
	g->map.x = ft_strlen(g->map.map_ptr[0]);
	temp = g->map.map_ptr;
	while (*temp)
	{
		temp++;
		len++;
	}
	g->map.y = len;
	mlx_set_window_size(g->mlx_ptr, g->map.x * TILE, g->map.y * TILE);
	mlx_get_monitor_size(0, &window.x, &window.y);
	if (window.x < g->map.x * TILE || window.y < g->map.y * TILE)
		exit_error(g, "Map is too big for display");
	spawn_objects(g);
	g->collectables = ft_calloc(g->map.amount_collectibles + 1,
			sizeof(t_collectable));
	if (!g->collectables)
		exit_error(g, "Memory allocation failed for collectables");
}

int	load_map(t_game *g, const char *map_name)
{
	int		fd;
	char	*line;
	char	*temp_ptr;
	char	*map_str;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		exit_error(g, "Could not open map file");
	map_str = malloc(sizeof(char));
	map_str[0] = '\0';
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp_ptr = ft_strjoin(map_str, line);
		free(map_str);
		free(line);
		if (!temp_ptr)
			return (0);
		map_str = temp_ptr;
	}
	if (!load_map_two(g, map_str, fd))
		return (0);
	return (1);
}

