/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 10:20:34 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/01/15 10:20:35 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init(t_env *env)
{
	env->player = (t_player*)malloc(sizeof(t_player));
	env->data = (t_data*)malloc(sizeof(t_data));
	env->ray = (t_ray*)malloc(sizeof(t_ray));
	env->player->posx = 1.5;
	env->player->posy = 1.5;
	env->player->dirx = 0;
	env->player->diry = 1;
	env->player->planex = 0.66;
	env->player->planey = 0;
	env->time = 0;
	env->oldtime = 0;
	env->move[0] = 0;
	env->move[1] = 0;
	env->move[2] = 0;
	env->move[3] = 0;
}

int		expose_hook(t_env *env)
{
	int		x;
	t_calc	*calc;
	char	*fps;

	x = -1;
	while (++x < WIDTH)
	{
		calc = (t_calc*)malloc(sizeof(t_calc));
		ft_calc_ray(env, calc, x);
		ft_set_step(env, calc);
		ft_calc_dist(env, calc);
		ft_calc_draw(env, calc);
		ft_trace_column(env, calc, x);
		env->zbuf[x] = calc->walldist;
		free(calc);
	}
	ft_check_move(env);
	fps = ft_calc_frametime(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_string_put(env->mlx, env->win, 10, 10, 0xffff00, fps);
	free(fps);
	return (0);
}

void	ft_delete(t_env *env)
{
	int		i;

	i = -1;
	while (env->text[++i])
	{
		mlx_destroy_image(env->mlx, env->text[i]->img);
		free(env->text[i]->data);
		free(env->text[i]);
	}
	i = -1;
	while (env->map[++i])
		free(env->map[i]);
	free(env->player);
	free(env->data);
	free(env->ray);
}

void	ft_free_env(t_env *env)
{
	int		i;

	i = 0;
	while (env->text[i])
	{
		free(env->text[i]->data);
		free(env->text[i]);
		i++;
	}
	i = 0;
	while (env->map[i])
		free(env->map[i++]);
	free(env->map);
	free(env->text);
	free(env->player);
	free(env->ray);
	free(env->data);
}

int		main(void)
{
	t_env			env;

	if ((env.mlx = mlx_init()))
	{
		ft_init(&env);
		if (!ft_consmap(&env))
			if ((env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "Wolf3d")))
				if ((env.img = mlx_new_image(env.mlx, WIDTH, HEIGHT)))
				{
					env.data->addr = mlx_get_data_addr(env.img, &env.data->bpp,
						&env.data->sl, &env.data->end);
					ft_load_text(&env);
					mlx_hook(env.win, KEYPRESS, KEYPRESSMASK, &key_press_hook,
						&env);
					mlx_hook(env.win, KEYRELEASE, KEYRELEASEMASK,
						&key_release_hook, &env);
					mlx_loop_hook(env.mlx, &expose_hook, &env);
					mlx_loop(env.mlx);
				}
		ft_free_env(&env);
	}
	return (0);
}
