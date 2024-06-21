/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/06/21 16:39:12 by sruff            ###   ########.fr       */
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
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
		check_next_tile(g, g->player.x, g->player.y - 1);
	else if ((key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
		check_next_tile(g, g->player.x, g->player.y + 1);
	else if ((key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
		check_next_tile(g, g->player.x - 1, g->player.y);
	else if ((key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT) && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT ))
		check_next_tile(g, g->player.x + 1, g->player.y);
	else if (key_data.key == MLX_KEY_ESCAPE)
	{
		ft_printf("ESC\n");
		cleanup_game(g);
		// mlx_destroy_window(g->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[0], old_x * TILE_SIZE, old_y * TILE_SIZE);
	if (old_x == g->map.exit_x && old_y == g->map.exit_y)
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[3], old_x * TILE_SIZE, old_y * TILE_SIZE);
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[1], g->player.x * TILE_SIZE, g->player.y * TILE_SIZE);
	(void)g;
}

int	main(int argc, char **argv)
{
	t_game	g;

	ft_memset(&g, 0, sizeof(t_game));
	if (argc != 2)
		exit_error(&g, "Input should look like \"./so_long <map.ber>\"");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 5))
		exit_error(&g, "Map file should have .ber extension");
	g.mlx_ptr = mlx_init(512, 512, "game of the year", false);
	// g.mlx_ptr->width
	// g.mlx_ptr->height
	// mlx_get_monitor_size(0, &win_x, &win_y); only works after you started/created a window already
	if (!g.mlx_ptr)
		exit_error(&g, "Failed to initialize MLX");
	if (!load_map(&g, argv[1]))
		exit_error(&g, "Failed to load map");
	create_visited(&g);
	if (!check_rectangle(&g) || !count_tiles(&g) || !collect_reachable(&g) || !check_walls(&g))
		exit_error(&g, "Invalid map");
	mlx_key_hook(g.mlx_ptr, key_press, &g);
	mlx_loop(g.mlx_ptr);
	cleanup_game(&g);
	system("leaks so_long");
	return (0);
}