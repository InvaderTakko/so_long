/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:48:39 by sruff             #+#    #+#             */
/*   Updated: 2024/06/21 15:20:22 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < IMG_NUM)
	{
		if (g->text.texture[i])
			mlx_delete_texture(g->text.texture[i]);
		if (g->text.img[i])
			mlx_delete_image(g->mlx_ptr, g->text.img[i]);
		i++;
	}
}

void	cleanup_game(t_game *g)
{
	if (g->map.map_ptr)
		free_map(g->map.map_ptr);
	if (g->map.visited)
		free_map(g->map.visited);
	if (g->collectables)
		free(g->collectables);
	free_textures(g);
	if (g->mlx_ptr)
		mlx_terminate(g->mlx_ptr);
}

void	exit_error(t_game *g, const char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	cleanup_game(g);
	system("leaks so_long");
	exit(EXIT_FAILURE);
}