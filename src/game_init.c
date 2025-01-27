/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:05:20 by abenajib          #+#    #+#             */
/*   Updated: 2025/01/27 12:44:30 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	ft_check_char(t_map_data *map, int x, int y, int num)
{
	if (num == GROUND_TEXTURE)
		return (map->map[y][x] == '0' || map->map[y][x] == 'E'
				|| map->map[y][x] == 'C' || map->map[y][x] == 'P'
				|| map->map[y][x] == '1');
	if (num == WALLS_TEXTURE)
		return (map->map[y][x] == '1');
	if (num == COLECTABLES_TEXTURE)
		return (map->map[y][x] == 'C');
	if (num == EXITS_TEXTURE)
		return (map->map[y][x] == 'E');
	if (num == PLAYER_TEXTURE)
		return (map->map[y][x] == 'P');
	return (false);
}

char	*ft_write_path(t_textures *textures, int num)
{
	if (num == GROUND_TEXTURE)
		return (textures->ground_path);
	if (num == WALLS_TEXTURE)
		return (textures->walls_path);
	if (num == COLECTABLES_TEXTURE)
		return (textures->colectables_path);
	if (num == EXITS_TEXTURE)
		return (textures->exit_path_0);
	if (num == PLAYER_TEXTURE)
		return (textures->player_path);
	return (NULL);
}

bool	ft_put_texture(mlx_t *mlx, t_map_data *map,
						t_textures *textures, int num)
{
	int		x;
	int		y;
	void	*texture;
	void	*image;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (ft_check_char(map, x, y, num))
			{
				texture = mlx_load_png(ft_write_path(textures, num));
				image = mlx_texture_to_image(mlx, texture);
				if (mlx_image_to_window(mlx, image, x * 64, y * 64) == -1)
					return (false);
				mlx_delete_texture(texture);
			}
			x++;
		}
		y++;
	}
	return (true);
}

void	ft_fill_textures(t_textures *textures)
{
	textures->ground_path = "textures/ground.png";
	textures->walls_path = "textures/wall.png";
	textures->colectables_path = "textures/colectable.png";
	textures->exit_path_0 = "textures/exit0.png";
	textures->player_path = "textures/player.png";
	textures->exit_path_1 = "textures/exit1.png";
}

void	**ft_get_textures(void **texture)
{
	texture = malloc(6 * sizeof(void *));
	texture[GROUND_TEXTURE] = mlx_load_png("textures/ground.png");
	texture[WALLS_TEXTURE] = mlx_load_png("textures/wall.png");
	texture[PLAYER_TEXTURE] = mlx_load_png("textures/player.png");
	texture[EXITS_TEXTURE] = mlx_load_png("textures/exit.png");
	texture[COLECTABLES_TEXTURE] = mlx_load_png("textures/colectable.png");
	return (texture);
}

void	ft_remove_textures(void **texture)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (texture[i] == NULL)
			i++;
		else
		{
			mlx_delete_texture(texture[i]);
			i++;
		}
	}
	free(texture);
	texture = NULL;
}

bool	ft_check_textures(void)
{
	void	**texture;
	int		i;

	i = 0;
	texture = NULL;
	texture = ft_get_textures(texture);
	while (i < 5)
	{
		if (texture[i] == NULL)
		{
			ft_remove_textures(texture);
			return (false);
		}
		i++;
	}
	ft_remove_textures(texture);
	return (true);
}

void ft_clone_map(t_game *game, t_map_data *map)
{
	game->map->collectables = map->collectables;
	game->map->exits = map->exits;
	game->map->height = map->height;
	game->map->players = game->map->players;
	game->map->map = ft_strdup_2d(map->map, map->height);
	game->map->valid = true;
	game->map->width = map->width;
}

bool ft_textures_so_long(t_game *game, t_map_data *map)
{
	t_textures	textures;

	ft_fill_textures(&textures);
	if (!ft_check_textures())
		return (ft_printf("Error | Failed to load textures!\n"), false);
	game->mlx = mlx_init(map->width * PIXELS, map->height * PIXELS, "so_long", false);
	if (!ft_put_texture(game->mlx, map, &textures, GROUND_TEXTURE))
		return (ft_printf("Error | Failed to put the GROUND_TEXTURE!\n"), false);
	if (!ft_put_texture(game->mlx, map, &textures, WALLS_TEXTURE))
		return (ft_printf("Error | Failed to put the WALLS_TEXTURE!\n"), false);
	if (!ft_put_texture(game->mlx, map, &textures, COLECTABLES_TEXTURE))
		return (ft_printf("Error | Failed to put the COLECTABLES_TEXTURE!\n"), false);
	if (!ft_put_texture(game->mlx, map, &textures, EXITS_TEXTURE))
		return (ft_printf("Error | Failed to put the EXITS_TEXTURE!\n"), false);
	return (true);
}

// void	put_player(t_game *game, char *str, int x, int y)
// {
// 	void	*texture;

// 	mlx_delete_image(game->mlx, game->img.player_image);
// 	texture = mlx_load_png(str);
// 	game->img.player_image = mlx_texture_to_image(game->mlx, texture);
// 	mlx_image_to_window(game->mlx, game->img.player_image, x, y);
// 	mlx_delete_texture(texture);
// }
void ft_put_player(t_game *game)
{
	void		*t;

	t = mlx_load_png("textures/player.png");
	game->img.player_image = mlx_texture_to_image(game->mlx, t);
	mlx_image_to_window(game->mlx, game->img.player_image, game->player_pos.x * 64, game->player_pos.y * 64);
}

// void ft_move_up(t_game *game, int x, int y)
// {

// 	if (game->map->map[y - 1][x] == '0' || game->map->map[y - 1][x] == 'C')
// 		game->img.player_image->instances->y -= PIXELS;
// }

// void ft_move_right(t_game *game, int x, int y)
// {

// 	if (game->map->map[y ][x + 1] == '0' || game->map->map[y ][x + 1] == 'C')
// 		game->img.player_image->instances->x += PIXELS ;
// }

// void ft_move_left(t_game *game, int x, int y)
// {

// 	if (game->map->map[y ][x - 1] == '0' || game->map->map[y ][x - 1] == 'C')
// 		game->img.player_image->instances->x -= PIXELS ;

// }

// void ft_move_down(t_game *game, int x, int y)
// {

// 	if (game->map->map[y + 1][x] == '0' || game->map->map[y + 1][x] == 'C')
// 		game->img.player_image->instances->y += PIXELS;
// }

// void ft_hook(void* param)
// {
// 	t_game *game;

// 	game = (t_game *)param;
// 	int y = game->img.player_image->instances[0].y / PIXELS;
// 	int x = game->img.player_image->instances[0].x / PIXELS;

// 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(game->mlx);
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
// 		ft_move_up(game, x, y);
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
// 		ft_move_down(game, x, y);
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		ft_move_left(game, x, y);
// 	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		ft_move_right(game, x, y);
// }

bool	ft_init_game(t_map_data *map)
{
	t_game		game;


	//set textures
	if (!ft_textures_so_long(&game, map))
		return (false);
	//allocate space for game map
	game.map = malloc(sizeof(t_map_data));
	if (!game.map)
		return (ft_printf("Error | Failed to allocate memory for game.map!\n"), false);
	// clone all the infos to game map
	ft_clone_map(&game, map);
	//set the player pos to game->player_pos
	ft_find_pos(map, &(game.player_pos), 'P');
	//draw the initiale state of the player
	ft_put_player(&game);
	//move the player
	// mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_key_hook(game.mlx, &my_keyhook, &game);
	mlx_loop(game.mlx);
	ft_free_2d(game.map->map, game.map->height);
	free(game.map);
	mlx_terminate(game.mlx);
	return (true);
}

void	ft_start_game(t_map_data *map)
{
	ft_printf("Game Start!\n");
	ft_init_game(map);
}
// ft_printf("=============================================\n");
