/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:13:10 by sruff             #+#    #+#             */
/*   Updated: 2024/06/24 15:44:02 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 50
# define IMG_NUM 5
# define IMG_TILE "./img/floors.png"
# define IMG_PLAYER "./img/dank.png"
# define IMG_WALL "./img/wall.png"
# define IMG_GOAL "./img/goal.png"
# define IMG_COLLECT "./img/collect.png"



# include <stdlib.h>
# include "./libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>


typedef struct s_collectable
{
	int x;
	int y;
	int collected;
}	t_collectable;
typedef struct s_texture
{
	mlx_image_t	*img[IMG_NUM];
	mlx_texture_t	*texture[IMG_NUM];
}	t_texture;
typedef struct s_map
{
	u_int32_t		x;
	u_int32_t		y;
	int				amount_collectibles;
	int				exit_x;
	int				exit_y;
	char			**visited;
	char 			prev;
	char	**map_ptr;
}	t_map;
typedef struct s_player
{
	int		x;
	int		y;
	int		steps;
	int		collected;
}	t_player;
typedef struct s_game
{
	void	*mlx_ptr;
	mlx_image_t *img;
	t_player	player;
	t_map	map;
	t_texture text;
	t_collectable *collectables;
	mlx_image_t *steps_img;
	
}	t_game;

void render_loop(void *param);
int load_map(t_game *g, const char *map_name);
void check_next_tile(t_game *g, int x, int y);
void	create_visited(t_game *g);
int flood_fill(t_game *g, int x, int y, int steps);
int	count_tiles(t_game *g);
int	check_rectangle(t_game *g);
int collect_reachable(t_game *g);
int	check_walls(t_game *g);
void	exit_error(t_game *g, const char *error_message);
void render_steps(t_game *g);
void exit_success(t_game *g, const char *message);
void	cleanup_game(t_game *g);
// void load_tile(t_game *g, char c , int x, int y);




#endif