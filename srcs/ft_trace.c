/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 14:15:00 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/02/11 14:15:03 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_trace_wall(t_env *env, t_calc *calc, int numtext, int x)
{
	int		color;
	int		y;

	numtext = (1) ? 2 : numtext;
	y = calc->drawstart;
	while (++y < calc->drawstop)
	{
		env->text[numtext]->d = y * 2 - HEIGHT + calc->lineh;
		env->text[numtext]->texy = ((env->text[numtext]->d *
			env->text[numtext]->height) / calc->lineh) / 2;
		color = ft_get_pixel_color(env->text[numtext]->texx,
			env->text[numtext]->texy, env->text[numtext]->data);
		if (calc->side)
			color = (color >> 1) & 8355711;
		ft_put_pixel_to_image(x, y, env, color);
	}
}

void	ft_trace_floor(t_env *env, t_calc *calc, int x)
{
	int		colorf;
	int		colorc;
	int		y;

	y = calc->drawstop;
	while (++y < HEIGHT)
	{
		env->text[0]->d = (HEIGHT / (double)(2 * y - HEIGHT)) /
			calc->walldist;
		env->text[0]->floorx = env->text[0]->d * env->text[0]
			->wallx + (1. - env->text[0]->d) * env->player->posx;
		env->text[0]->floory = env->text[0]->d * env->text[0]
			->wally + (1. - env->text[0]->d) * env->player->posy;
		env->text[0]->texx = (int)(env->text[0]->floorx *
			env->text[0]->width) % env->text[0]->width;
		env->text[0]->texy = (int)(env->text[0]->floory *
			env->text[0]->height) % env->text[0]->height;
		colorf = ft_get_pixel_color(env->text[0]->texx,
			env->text[0]->texy, env->text[0]->data);
		colorc = ft_get_pixel_color(env->text[0]->texx,
			env->text[0]->texy, env->text[1]->data);
		ft_put_pixel_to_image(x, HEIGHT - y, env, colorc);
		ft_put_pixel_to_image(x, y, env, colorf);
	}
}

void	ft_trace_column(t_env *env, t_calc *calc, int x)
{
	ft_calc_wall(env, calc, env->map[calc->mapx][calc->mapy]);
	ft_trace_wall(env, calc, env->map[calc->mapx][calc->mapy], x);
	ft_calc_floor(env, calc);
	ft_trace_floor(env, calc, x);
}

void	ft_set_step(t_env *env, t_calc *calc)
{
	if (env->ray->dirx < 0)
	{
		calc->stepx = -1;
		calc->sidedistx = (env->ray->posx - calc->mapx) * calc->deltadistx;
	}
	else
	{
		calc->stepx = 1;
		calc->sidedistx = (calc->mapx + 1. - env->ray->posx) * calc->deltadistx;
	}
	if (env->ray->diry < 0)
	{
		calc->stepy = -1;
		calc->sidedisty = (env->ray->posy - calc->mapy) * calc->deltadisty;
	}
	else
	{
		calc->stepy = 1;
		calc->sidedisty = (calc->mapy + 1. - env->ray->posy) * calc->deltadisty;
	}
}

char	*ft_calc_frametime(t_env *env)
{
	char	*fps;
	char	*tmp;
	char	*tmp2;

	fps = ft_strdup("FPS : ");
	env->oldtime = env->time;
	env->time = clock();
	env->frametime = (env->time - env->oldtime) / 1000000.0;
	tmp = ft_strdup(fps);
	free(fps);
	tmp2 = ft_itoa((int)(1 / env->frametime));
	fps = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (fps);
}
