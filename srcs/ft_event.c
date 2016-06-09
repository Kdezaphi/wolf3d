/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 14:11:55 by kdezaphi          #+#    #+#             */
/*   Updated: 2016/02/24 13:04:15 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_release_hook(int keycode, t_env *env)
{
	if (keycode == 123)
		env->move[0] = 0;
	if (keycode == 126)
		env->move[1] = 0;
	if (keycode == 124)
		env->move[2] = 0;
	if (keycode == 125)
		env->move[3] = 0;
	return (0);
}

int		key_press_hook(int keycode, t_env *env)
{
	if (keycode == 123)
		env->move[0] = 1;
	if (keycode == 126)
		env->move[1] = 1;
	if (keycode == 124)
		env->move[2] = 1;
	if (keycode == 125)
		env->move[3] = 1;
	if (keycode == 53)
	{
		ft_delete(env);
		exit(0);
	}
	return (0);
}

void	ft_player_move(int up, t_env *env)
{
	double	move;

	move = env->frametime * 2.5;
	if (up)
	{
		if (env->map[(int)(env->player->posx + env->player->dirx * move)]
			[(int)(env->player->posy)] < 2)
			env->player->posx += env->player->dirx * move;
		if (env->map[(int)(env->player->posx)]
			[(int)(env->player->posy + env->player->diry * move)] < 2)
			env->player->posy += env->player->diry * move;
	}
	else
	{
		if (env->map[(int)(env->player->posx - env->player->dirx * move)]
			[(int)(env->player->posy)] < 2)
			env->player->posx -= env->player->dirx * move;
		if (env->map[(int)(env->player->posx)]
			[(int)(env->player->posy - env->player->diry * move)] < 2)
			env->player->posy -= env->player->diry * move;
	}
}

void	ft_player_rota(double rota, t_env *env)
{
	double	oldplaydirx;
	double	oldplayplanex;

	oldplaydirx = env->player->dirx;
	oldplayplanex = env->player->planex;
	env->player->dirx = env->player->dirx * cos(rota)
	- env->player->diry * sin(rota);
	env->player->diry = oldplaydirx * sin(rota) + env->player->diry * cos(rota);
	env->player->planex = env->player->planex * cos(rota)
	- env->player->planey * sin(rota);
	env->player->planey = oldplayplanex * sin(rota)
	+ env->player->planey * cos(rota);
}

void	ft_check_move(t_env *env)
{
	if (env->move[0])
		ft_player_rota(env->frametime * 3.0, env);
	if (env->move[1])
		ft_player_move(1, env);
	if (env->move[2])
		ft_player_rota(-env->frametime * 3.0, env);
	if (env->move[3])
		ft_player_move(0, env);
}
