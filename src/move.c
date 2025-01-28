
#include "../include/so_long.h"

void	free_2d(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			free(s[i++]);
		free(s);
	}
}
//-----------------------------------moves----------------------------------



void	put_exit(t_game *game, mlx_t *mlx)
{
	int		x;
	int		y;
	void	*texture;
	void	*img;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == 'E' && game->map->collectables != 0)
				texture = mlx_load_png("textures/exit0.png");
			if (game->map->map[y][x] == 'E' && game->map->collectables == 0)
				texture = mlx_load_png("textures/exit1.png");
			if (game->map->map[y][x] == 'E')
			{
				img = mlx_texture_to_image(mlx, texture);
				mlx_image_to_window(mlx, img, x * PIXELS, y * PIXELS);
				mlx_delete_texture(texture);
			
			}
			x++;
		}
		y++;
	}
}
void	take_coin(t_game *game, int x, int y)
{
	void	*texture;
	void	*img;


	if (game->map->map[y][x] == 'C')
	{
		game->map->collectables -= 1;
		game->map->map[y][x] = '0';
		ft_putnbr(game->map->collectables);
		texture = mlx_load_png("textures/ground.png");
		img = mlx_texture_to_image(game->mlx, texture);
		mlx_image_to_window(game->mlx, img, x * PIXELS, y * PIXELS);
		mlx_delete_texture(texture);
		if (game->map->collectables == 0)
		{
			remove_exit(game, game->mlx);
			put_exit(game, game->mlx);
		}
		mlx_image_to_window(game->mlx, game->img.player_image, x * PIXELS, y * PIXELS);
	}
	else if (game->map->map[y][x] == 'E' && game->map->collectables == 0)
	{
		free_2d(game->map->map);
		exit(EXIT_SUCCESS);
	}
}

void	horizontal(mlx_key_data_t keydata, t_game *game, int x, int y)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action && game->map->map[y][x - 1] != '1')
	{
		if (game->map->map[y][x - 1] == '0' || game->map->map[y][x - 1] == 'C' ||
			game->map->map[y][x - 1] == 'P' || (game->map->map[y][x - 1] == 'E' && game->map->collectables == 0))
		{
			game->img.player_image->instances->x -= PIXELS;
			my_put_player(game, "textures/player.png", (x - 1) * PIXELS, y * PIXELS);
			take_coin(game, x - 1, y);
		}
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action && game->map->map[y][x + 1] != '1')
	{
		if (game->map->map[y][x + 1] == '0' || game->map->map[y][x + 1] == 'C' ||
			game->map->map[y][x + 1] == 'P' || (game->map->map[y][x + 1] == 'E' && game->map->collectables == 0))
		{
			// prnt_move(++s->moves);
			game->img.player_image->instances->x += PIXELS;
			my_put_player(game, "textures/player.png", (x + 1) * PIXELS, y * PIXELS);
			take_coin(game, x + 1, y);
		}
	}
}
void	vertical(mlx_key_data_t keydata, t_game *game, int x, int y)
{
	if (keydata.key == MLX_KEY_UP && keydata.action && game->map->map[y - 1][x] != '1')
	{
		if (game->map->map[y - 1][x] == '0' || game->map->map[y - 1][x] == 'C' ||
			game->map->map[y - 1][x] == 'P' || (game->map->map[y - 1][x] == 'E' && game->map->collectables == 0))
		{
			// prnt_move(++moves);
			game->img.player_image->instances->y -= PIXELS;
			my_put_player(game, "textures/player.png", (x) * PIXELS, (y -1) * PIXELS);
			take_coin(game, x, y - 1);
		}
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action && game->map->map[y + 1][x] != '1')
	{
		if (game->map->map[y + 1][x] == '0' || game->map->map[y + 1][x] == 'C' ||
			game->map->map[y + 1][x] == 'P' || (game->map->map[y + 1][x] == 'E' && game->map->collectables == 0))
		{
			// prnt_move(++s->moves);
			game->img.player_image->instances->y += PIXELS;
			my_put_player(game, "textures/player.png", (x) * PIXELS, (y + 1) * PIXELS);
			take_coin(game, x , y + 1);
		}
	}
}


void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)param;
	x = game->img.player_image->instances->x / PIXELS;
	y = game->img.player_image->instances->y / PIXELS;

	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		horizontal(keydata, game, x, y);
	else if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		vertical(keydata, game, x, y);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
	}
}
