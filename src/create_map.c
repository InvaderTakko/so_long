/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:47:28 by sruff             #+#    #+#             */
/*   Updated: 2024/06/16 18:28:52 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void load_tile(t_game *g, char c , int x, int y)
{
	if (c == '0')
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[0], x * TILE_SIZE, y * TILE_SIZE);
	else if (c == '1')
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[2], x * TILE_SIZE, y * TILE_SIZE);
	else if (c == 'E')
	{
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[3], x * TILE_SIZE, y * TILE_SIZE);
		g->map.exit_x = x;
		g->map.exit_y = y;
	}	
	else if (c == 'P')
	{
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[1], x * TILE_SIZE, y * TILE_SIZE);
		g->player.x = x;
		g->player.y = y;
	}
	else if (c == 'C')
	{
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[0], x * TILE_SIZE, y * TILE_SIZE);
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[4], x * TILE_SIZE, y * TILE_SIZE);
		g->map.amount_collectibles++;
	}
}

static void load_pngs(t_game *g)
{
	int	i = 0;
	(g->text.texture)[0] = mlx_load_png(IMG_TILE);
	(g->text.texture)[1] = mlx_load_png(IMG_PLAYER);
	(g->text.texture)[2] = mlx_load_png(IMG_WALL);
	(g->text.texture)[3] = mlx_load_png(IMG_GOAL);
	(g->text.texture)[4] = mlx_load_png(IMG_COLLECT);
	while (i <= 4)
	{
		(g->text.img)[i] = mlx_texture_to_image(g->mlx_ptr, (g->text.texture)[i]);
		mlx_resize_image((g->text.img)[i], TILE_SIZE, TILE_SIZE);
		i++;
	}
}

static void	spawn_objects(t_game *g)
{
	u_int32_t x = 0;
	u_int32_t y = 0;
	char **map = g->map.map_ptr;
	char	c;

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
		// ft_printf("i get to second Y");
		y++;
	}
}

static void	set_map(t_game *g, char *map_str)
{
	char	**temp;
	int		len;

	len = 0;
	g->map.map_ptr = ft_split(map_str, '\n');
	free(map_str);
	g->map.x = ft_strlen(g->map.map_ptr[0]);
	// g->map.y = ft_strlen(g->map.map_ptr);
	temp = g->map.map_ptr;
	while (*temp)
	{
		temp++;
		len++;
	}
	g->map.y = len;
	mlx_set_window_size(g->mlx_ptr, g->map.x * TILE_SIZE, g->map.y * TILE_SIZE);
	ft_printf("Map: X: %d Y: %d\n", g->map.x, g->map.y);
	// render_map(g);
	spawn_objects(g);
	
}


int load_map(t_game *g, const char *map_name)
{
	int		fd;
	char	*line;
	char	*temp_ptr;
	char	*map_str;
	
	map_name = NULL;
	fd = open("/Users/sruff/Desktop/42Projects/so_long/maps/map.ber", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: could not open file\n");
		exit(EXIT_FAILURE);
	}
	map_str = malloc(sizeof(char));
	map_str[0] =  '\0';
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			// free(line);
			break ;
		}	
		temp_ptr = ft_strjoin(map_str, line);
		free(map_str);
		free(line);
		if (!temp_ptr)
			return 0;
		map_str = temp_ptr;
		
	}
	ft_printf("after GNL loop\n");
	if	(map_str && *map_str)
		set_map(g, map_str);
	else
		return (ft_printf("map is empty \n"), 0);
	// free(map_str);	
	// create_visited(g);
	close(fd);
	return 1;
}