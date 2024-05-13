/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:06:27 by sruff             #+#    #+#             */
/*   Updated: 2024/05/13 18:58:36 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	g;
	
	if (argc != 2)
	{
		ft_printf("Error: input should look like \"./so_long <map.ber>\"\n ");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) -4, ".ber"))
	{
		ft_printf("Error: input should look like \"./so_long <map.ber>\"\n ");
		exit(EXIT_FAILURE);
	}
	g.mlx_ptr = mlx_init(512, 512, "game of the year", true); 
	if (!g.mlx_ptr)
		exit(EXIT_FAILURE);
	mlx_new_image(g.mlx_ptr, 100, 100);
	return (0);	
}