/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/06/02 16:30:18 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


static void key_press(mlx_key_data_t key_data, void *param)
{
	t_game *g = (t_game *)param;
	// ft_printf("Keycode: %d\n", key_data.key);
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
	{
		g->player.y -= 10;
		ft_printf("UP\n");
	}
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
	{
		g->player.y += 10;
		ft_printf("DOWN\n");
	}
	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
	{
		g->player.x -= 10;
		ft_printf("LEFT\n");
	}
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
	{
		g->player.x += 10;
		ft_printf("RIGHT\n");
	}
	else if (key_data.key == MLX_KEY_ESCAPE)
	{
		ft_printf("ESC\n");
		exit(EXIT_SUCCESS);
	}
	(void)g;
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
	
}


static void load_map(t_game *g, const char *map_name)
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
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ; //free line
		temp_ptr = ft_strjoin(map_str, line);
		free(map_str);
		free(line);
		map_str = temp_ptr;
		
	}
	ft_printf("after GNL loop\n");
	set_map(g, map_str);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_game	g;
	
	if (argc != 2)
	{
		ft_printf("Error: input should look like \"./so_long <map.ber>\"\n ");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) -4, ".ber", 5))
	{
		ft_printf("Error: input should look like \"./so_long <map.ber>\"\n ");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_printf("Map: good\n");
	}
	// init_game(&g, argv[1]);
	g.mlx_ptr = mlx_init(512, 512, "game of the year", true);
	load_map(&g, argv[1]);
	g.text.texture = mlx_load_png("/Users/sruff/Desktop/42Projects/so_long/dank.png");
	// render_map
	mlx_key_hook(g.mlx_ptr, key_press, &g);
	mlx_loop_hook(g.mlx_ptr, render_loop, &g);

	mlx_loop(g.mlx_ptr);
	if (!g.mlx_ptr)
		exit(EXIT_FAILURE);
	return (0);	
}