/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:13:10 by sruff             #+#    #+#             */
/*   Updated: 2024/05/13 17:27:20 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_game
{
	void	*mlx_ptr;
	t_player	player;
	t_map	map;
	
}	t_game;

typedef struct s_player
{
	int		x;
	int		y;
	int		steps;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
}	t_map;