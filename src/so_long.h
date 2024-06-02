/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:13:10 by sruff             #+#    #+#             */
/*   Updated: 2024/06/02 14:40:25 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 50

# include <stdlib.h>
# include "./libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>

typedef struct s_texture
{
	mlx_image_t	*img;
	mlx_texture_t	*texture;
}	t_texture;
typedef struct s_map
{
	u_int32_t		x;
	u_int32_t		y;
	char	**map_ptr;
}	t_map;
typedef struct s_player
{
	int		x;
	int		y;
	int		steps;
}	t_player;
typedef struct s_game
{
	void	*mlx_ptr;
	mlx_image_t *img;
	t_player	player;
	t_map	map;
	t_texture text;
	
}	t_game;





#endif