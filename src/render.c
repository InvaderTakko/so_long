/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:23:52 by sruff             #+#    #+#             */
/*   Updated: 2024/06/02 16:25:24 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void dank_load(void *param)
{
	
	// mlx_image_t *img;
	t_game *g = (t_game *)param;
	// g->text.texture = mlx_load_png("/Users/sruff/Desktop/42Projects/so_long/dank.png");
	// ft_printf("texture: %p\n", g->text.texture);
	g->text.img = mlx_texture_to_image(g->mlx_ptr, g->text.texture);
	// ft_printf("img: %p\n", g->text.img);
	if (!mlx_resize_image(g->text.img, 100, 100))
		   return;	
	mlx_image_to_window(g->mlx_ptr, g->text.img, g->player.x, g->player.y);
}

static int32_t random_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static void	set_pixels(void *param)
{
	u_int32_t x;
	u_int32_t y;
	// mlx_texture_t *texture = mlx_load_png("/Users/sruff/Desktop/42Projects/so_long/dank.png");
	// mlx_image_t *img;
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
	// img = mlx_texture_to_image(g->mlx_ptr, texture);
	// if (!mlx_resize_image(img, 300, 300))
    //        return;	
    mlx_image_to_window(g->mlx_ptr, g->img, 0, 0);
	// mlx_image_to_window(g->mlx_ptr, img, 0, 0);
	// mlx_load_png("./dank.png");

}
void render_loop(void *param)
{
	t_game *g = (t_game *)param;
	// mlx_image_to_window(g->mlx_ptr, g->img, 0, 0);
	set_pixels(g);
	dank_load(g);
}