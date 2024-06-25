/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/06/25 16:36:32 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_steps(t_game *g)
{
	char	*steps_num;
	char	*steps_str;

	if (g->steps_img)
		mlx_delete_image(g->mlx_ptr, g->steps_img);
	steps_num = ft_itoa(g->player.steps);
	if (!steps_num)
		exit_error(g, "Memory allocation failed for ft_itoa");
	steps_str = ft_strjoin("Steps: ", steps_num);
	free(steps_num);
	if (!steps_str)
		exit_error(g, "Memory allocation failed for ft_strjoin");
	g->steps_img = mlx_put_string(g->mlx_ptr, steps_str, 10, 10);
	free(steps_str);
	if (!g->steps_img)
		exit_error(g, "Failed to render steps on screen");
}

static void	check_input_key(t_game *g, mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		check_next_tile(g, g->player.x, g->player.y - 1);
	else if ((key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		check_next_tile(g, g->player.x, g->player.y + 1);
	else if ((key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		check_next_tile(g, g->player.x - 1, g->player.y);
	else if ((key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		check_next_tile(g, g->player.x + 1, g->player.y);
	else if (key_data.key == MLX_KEY_ESCAPE)
	{
		cleanup_game(g);
		exit(EXIT_SUCCESS);
	}
}

static void	key_press(mlx_key_data_t key_data, void *param)
{
	t_game	*g;
	int		old_y;
	int		old_x;

	g = (t_game *)param;
	old_y = g->player.y;
	old_x = g->player.x;
	check_input_key(g, key_data);
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[0],
		old_x * TILE, old_y * TILE);
	if (old_x == g->map.exit_x && old_y == g->map.exit_y)
		mlx_image_to_window(g->mlx_ptr, (g->text.img)[3],
			old_x * TILE, old_y * TILE);
	mlx_image_to_window(g->mlx_ptr, (g->text.img)[1],
		g->player.x * TILE, g->player.y * TILE);
	render_steps(g);
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
	if (!g.mlx_ptr)
		exit_error(&g, "Failed to initialize MLX");
	if (!load_map(&g, argv[1]))
		exit_error(&g, "Failed to load map");
	create_visited(&g);
	if (!check_rectangle(&g) || !count_tiles(&g) || !collect_reachable(&g)
		|| !check_walls(&g))
		exit_error(&g, "Invalid map");
	render_steps(&g);
	mlx_key_hook(g.mlx_ptr, key_press, &g);
	mlx_loop(g.mlx_ptr);
	cleanup_game(&g);
	return (0);
}
