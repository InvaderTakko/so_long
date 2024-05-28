/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/05/28 17:52:42 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int32_t random_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static void	set_pixels(void *param)
{
	u_int32_t x;
	u_int32_t y;
    (void)param;
    t_game *g = (t_game *)param;
    g->img = mlx_new_image(g->mlx_ptr, (g->map.x * TILE_SIZE), (g->map.y * TILE_SIZE));
    y = 0;
    while (y < g->map.y * TILE_SIZE)
    {
       x = 0;
        while (x < g->map.x * TILE_SIZE)
        {	
            uint32_t color = random_pixel(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF, rand() % 0xFF);
            mlx_put_pixel(g->img, x, y, color); 
            x++;
        }
        y++;
    }
    mlx_image_to_window(g->mlx_ptr, g->img, 0, 0);
}
static void render_map(t_game *g)
{
    g->img = mlx_new_image(g->mlx_ptr, (g->map.x * TILE_SIZE), (g->map.y * TILE_SIZE));
    // For now, just fill with a single color
	// mlx_image_to_window(g->mlx_ptr, g->img, g->map.x * TILE_SIZE, g->map.y * TILE_SIZE);
	// mlx_put_pixel(g->img, g->map.x * TILE_SIZE, g->map.y * TILE_SIZE, 16711680);
    
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
	render_map(g);
	
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
	// render_map
	mlx_loop_hook(g.mlx_ptr, set_pixels, &g);
	// mlx_loop_hook(g.mlx_ptr, ft_hook, mlx);

	mlx_loop(g.mlx_ptr);
	if (!g.mlx_ptr)
		exit(EXIT_FAILURE);
	// mlx_new_image(g.mlx_ptr, 100, 100);
	return (0);	
}