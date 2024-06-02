/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/06/02 20:11:21 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void update_render(void *param)
// {
	
// }

static void key_press(mlx_key_data_t key_data, void *param)
{
	t_game *g = (t_game *)param;
	// ft_printf("Keycode: %d\n", key_data.key);
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
	{
		g->player.y -= 1;
		ft_printf("UP\n");
	}
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
	{
		g->player.y += 1;
		ft_printf("DOWN\n");
	}
	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
	{
		g->player.x -= 1;
		ft_printf("LEFT\n");
	}
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
	{
		g->player.x += 1;
		ft_printf("RIGHT\n");
		
	}
	else if (key_data.key == MLX_KEY_ESCAPE)
	{
		ft_printf("ESC\n");
		// mlx_destroy_window(g->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
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
	// window_size_t window_size = {1, 1};
	
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
	// mlx_get_monitor_size(0, &window_size.x, &window_size.y);
	// ft_printf("X: %d Y: %d\n", window_size.x, window_size.y);
	// g.mlx_ptr = mlx_init(window_size.x, window_size.y, "game of the year", true);
	g.mlx_ptr = mlx_init(512, 512, "game of the year", true);
	load_map(&g, argv[1]);
	// g.text.texture = mlx_load_png("/Users/sruff/Desktop/42Projects/so_long/dank.png");
	// render_map
	mlx_key_hook(g.mlx_ptr, key_press, &g);
	// mlx_loop_hook()
	// mlx_loop_hook(g.mlx_ptr, render_loop, &g);
	
	mlx_loop(g.mlx_ptr);
	mlx_terminate(g.mlx_ptr);
	if (!g.mlx_ptr)
		exit(EXIT_FAILURE);
	return (0);	
}