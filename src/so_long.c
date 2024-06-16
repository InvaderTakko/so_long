/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/06/16 19:25:07 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void update_render(void *param)
// {
	
// }

static void key_press(mlx_key_data_t key_data, void *param)
{
	t_game *g = (t_game *)param;
	int	old_y;
	int	old_x;

	old_y = g->player.y;
	old_x = g->player.x;
	// ft_printf("Keycode: %d\n", key_data.key);
	// if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
	{
		// g->player.y -= 1;
		check_next_tile(g, g->player.x, g->player.y - 1);
		// ft_printf("UP\n");
		// ft_printf("Steps: %d\n", g->player.steps);
	}
	else if ((key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
	{
		// g->player.y += 1;
		check_next_tile(g, g->player.x, g->player.y + 1);
		// ft_printf("DOWN\n");
	}
	else if ((key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
	{
		// g->player.x -= 1;
		check_next_tile(g, g->player.x - 1, g->player.y);
		// ft_printf("LEFT\n");
	}
	else if ((key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
	{
		// g->player.x += 1;
		check_next_tile(g, g->player.x + 1, g->player.y);
		// ft_printf("RIGHT\n");
		
	}
	else if (key_data.key == MLX_KEY_ESCAPE)
	{
		ft_printf("ESC\n");
		// mlx_destroy_window(g->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[0], old_x * TILE_SIZE, old_y * TILE_SIZE);
	if (old_x == g->map.exit_x && old_y == g->map.exit_y)
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[3], old_x * TILE_SIZE, old_y * TILE_SIZE);
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[1], g->player.x * TILE_SIZE, g->player.y * TILE_SIZE);

	// update_render(param);
	(void)g;
}

// static void key_press(mlx_key_data_t key_data, void *param)
// {
// 	t_game *g = (t_game *)param;
// 	// ft_printf("Keycode: %d\n", key_data.key);
// 	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
// 	{
// 		g->player.y -= 50;
// 		ft_printf("UP\n");
// 	}
// 	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
// 	{
// 		g->player.y += 50;
// 		ft_printf("DOWN\n");
// 	}
// 	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
// 	{
// 		g->player.x -= 50;
// 		ft_printf("LEFT\n");
// 	}
// 	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
// 	{
// 		g->player.x += 50;
// 		ft_printf("RIGHT\n");
		
// 	}
// 	else if (key_data.key == MLX_KEY_ESCAPE)
// 	{
// 		ft_printf("ESC\n");
// 		// mlx_destroy_window(g->mlx_ptr);
// 		exit(EXIT_SUCCESS);
// 	}
// 	mlx_image_to_window(g->mlx_ptr, (g->text.img)[1], g->player.x * TILE_SIZE, g->player.y * TILE_SIZE);
// 	// update_render(param);
// 	(void)g;
// }

int	main(int argc, char **argv)
{
	t_game	g;
	// int32_t win_x;
	// int32_t win_y;
	
	// win_x = 1;
	// win_y = 1;
	g.player.steps = 0;
	g.map.amount_collectibles = 0;
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
		ft_printf("Map: exists\n");
	}
	// init_game(&g, argv[1]);
	
	// ft_printf("X: %d Y: %d\n", window_size.x, window_size.y);
	// g.mlx_ptr = mlx_init(window_size.x, window_size.y, "game of the year", true);
	// mlx_get_monitor_size(0, &win_x, &win_y);
	g.mlx_ptr = mlx_init(512, 512, "game of the year", true);

	if (!load_map(&g, argv[1]))
		return 1;
	create_visited(&g);
	if (!check_rectangle(&g) || !count_tiles(&g) || !collect_reachable(&g))
		return (ft_printf("map sucks"), 1);
	// g.text.texture = mlx_load_png("/Users/sruff/Desktop/42Projects/so_long/dank.png");
	// render_map
	mlx_key_hook(g.mlx_ptr, key_press, &g);
	// mlx_loop_hook()
	// mlx_loop_hook(g.mlx_ptr, render_loop, &g);
	
	mlx_loop(g.mlx_ptr);
	mlx_terminate(g.mlx_ptr);

	if (!g.mlx_ptr)
		exit(EXIT_FAILURE);
	char command[256];
	sprintf(command, "leaks %d", getpid());
	system(command);
	return (0);	
}