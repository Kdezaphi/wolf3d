/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 14:18:11 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/02/11 14:18:12 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_pixel_to_image(int x, int y, t_env *env, int color)
{
	t_color	unc;
	int		i;
	int		end;

	unc.cv = mlx_get_color_value(env->mlx, color);
	i = 0;
	while (i < (env->data->bpp / 8))
	{
		if (!env->data->end)
			end = i;
		else
			end = 3 - i;
		env->data->addr[((env->data->bpp / 8) * x) + (y * env->data->sl) + i] =
			unc.oct[end];
		i++;
	}
}

int		ft_get_pixel_color(int x, int y, t_data *data)
{
	t_color unc;
	int		i;
	int		end;

	i = 0;
	while (i < (data->bpp / 8))
	{
		if (!data->end)
			end = i;
		else
			end = 3 - i;
		unc.oct[end] = data->addr[((data->bpp / 8) * x) + (y * data->sl) + i];
		i++;
	}
	return (unc.cv);
}
