/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 14:13:39 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/02/11 14:13:40 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_calc_ray(t_env *env, t_calc *calc, int x)
{
	calc->hit = 0;
	env->ray->poscam = 2 * x / (double)WIDTH - 1.;
	env->ray->posx = env->player->posx;
	env->ray->posy = env->player->posy;
	env->ray->dirx = env->player->dirx + env->player->planex * env->ray->poscam;
	env->ray->diry = env->player->diry + env->player->planey * env->ray->poscam;
	calc->mapx = (int)env->ray->posx;
	calc->mapy = (int)env->ray->posy;
	calc->deltadistx = sqrt(1 + (env->ray->diry * env->ray->diry)
		/ (env->ray->dirx * env->ray->dirx));
	calc->deltadisty = sqrt(1 + (env->ray->dirx * env->ray->dirx)
		/ (env->ray->diry * env->ray->diry));
}

void	ft_calc_dist(t_env *env, t_calc *calc)
{
	while (!calc->hit)
	{
		if (calc->sidedistx < calc->sidedisty)
		{
			calc->sidedistx += calc->deltadistx;
			calc->mapx += calc->stepx;
			calc->side = 0;
		}
		else
		{
			calc->sidedisty += calc->deltadisty;
			calc->mapy += calc->stepy;
			calc->side = 1;
		}
		if (env->map[calc->mapx][calc->mapy] > 0)
			calc->hit = 1;
	}
}

void	ft_calc_draw(t_env *env, t_calc *calc)
{
	if (calc->side)
		calc->walldist = fabs((calc->mapy - env->ray->posy
			+ (1 - calc->stepy) / 2) / env->ray->diry);
	else
		calc->walldist = fabs((calc->mapx - env->ray->posx
			+ (1 - calc->stepx) / 2) / env->ray->dirx);
	calc->lineh = abs((int)(HEIGHT / calc->walldist));
	calc->drawstart = (HEIGHT - calc->lineh) / 2;
	if (calc->drawstart < 0)
		calc->drawstart = 0;
	calc->drawstop = (HEIGHT + calc->lineh) / 2;
	if (calc->drawstop >= HEIGHT || calc->drawstop < 0)
		calc->drawstop = HEIGHT - 1;
}

void	ft_calc_wall(t_env *env, t_calc *calc, int numtext)
{
	numtext = (1) ? 2 : numtext;
	if (calc->side)
		calc->wallx = env->ray->posx + ((calc->mapy -
			env->ray->posy + (1 - calc->stepy) / 2) / env->ray->diry) *
			env->ray->dirx;
	else
		calc->wallx = env->ray->posy + ((calc->mapx -
			env->ray->posx + (1 - calc->stepx) / 2) / env->ray->dirx) *
			env->ray->diry;
	calc->wallx -= floor(calc->wallx);
	env->text[numtext]->texx = (int)(calc->wallx *
		(double)env->text[numtext]->width);
	if (!calc->side && env->ray->dirx > 0)
		env->text[numtext]->texx = env->text[numtext]->width -
			env->text[numtext]->texx - 1;
	if (calc->side && env->ray->diry < 0)
		env->text[numtext]->texx = env->text[numtext]->width -
			env->text[numtext]->texx - 1;
}

void	ft_calc_floor(t_env *env, t_calc *calc)
{
	if (!calc->side)
	{
		if (env->ray->dirx > 0)
			env->text[0]->wallx = calc->mapx;
		else
			env->text[0]->wallx = calc->mapx + 1.0;
		env->text[0]->wally = calc->mapy + calc->wallx;
	}
	else
	{
		env->text[0]->wallx = calc->mapx + calc->wallx;
		if (env->ray->diry > 0)
			env->text[0]->wally = calc->mapy;
		else
			env->text[0]->wally = calc->mapy + 1.0;
	}
}
