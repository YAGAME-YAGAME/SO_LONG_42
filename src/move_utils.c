/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:08:13 by yagame            #+#    #+#             */
/*   Updated: 2025/01/28 14:03:57 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	my_put_player(t_game *game, char *str, int x, int y)
{
	void	*texture;

	mlx_delete_image(game->mlx, game->img.player_image);
	texture = mlx_load_png(str);
	game->img.player_image = mlx_texture_to_image(game->mlx, texture);
	mlx_image_to_window(game->mlx, game->img.player_image, x, y);
	mlx_delete_texture(texture);
}


void	remove_exit(t_game *game, mlx_t *mlx)
{
	void	*texture;
	void	*img;
	int		i;
	int		len;

	i = 0;
	while (game->map->map[i])
	{
		len = 0;
		while (game->map->map[i][len])
		{
			if (game->map->map[i][len] == 'E')
			{
				texture = mlx_load_png("textures/ground.png");
				img = mlx_texture_to_image(mlx, texture);
				mlx_image_to_window(mlx, img, len * PIXELS, i * PIXELS);
				mlx_delete_texture(texture);
				return ;
			}
			len++;
		}
		i++;
	}
}


void	ft_putchar(char c)
{
	write(1, &c, 1);
}
void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}
