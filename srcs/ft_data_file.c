/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <kdezaphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 14:16:51 by kdezaphi          #+#    #+#             */
/*   Updated: 2016/06/09 14:03:19 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_count_line(int fd, char *line)
{
	int		nb_line;

	nb_line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		nb_line++;
		free(line);
	}
	free(line);
	return (nb_line);
}

int		ft_consline(t_env *env, char *line, int nb_line)
{
	char	**tab;
	int		nb_col;

	tab = ft_strsplit(line, ' ');
	nb_col = 0;
	while (tab[nb_col])
		nb_col++;
	env->map[nb_line] = (int*)malloc(sizeof(int) * (nb_col + 1));
	env->map[nb_line][nb_col] = 100;
	nb_col = 0;
	while (tab[nb_col])
	{
		env->map[nb_line][nb_col] = ft_atoi(tab[nb_col]);
		nb_col++;
	}
	nb_col = 0;
	while (tab[nb_col])
		free(tab[nb_col++]);
	free(tab);
	return (1);
}

int		ft_consmap(t_env *env)
{
	char	*line;
	int		nb_line;
	int		fd;

	line = NULL;
	if ((fd = open("./maplaby.txt", O_RDONLY)) > 2)
	{
		nb_line = ft_count_line(fd, line);
		env->map = (int**)malloc(sizeof(int*) * (nb_line + 1));
		env->map[nb_line] = NULL;
	}
	close(fd);
	if ((fd = open("./maplaby.txt", O_RDONLY)) > 2)
	{
		nb_line = 0;
		while (get_next_line(fd, &line) > 0)
		{
			nb_line += ft_consline(env, line, nb_line);
			free(line);
		}
		free(line);
	}
	close(fd);
	return (0);
}

void	ft_set_text(t_env *env, char *line, int nb_line)
{
	env->text[nb_line] = (t_text*)malloc(sizeof(t_text));
	env->text[nb_line]->data = (t_data*)malloc(sizeof(t_data));
	env->text[nb_line]->img = mlx_xpm_file_to_image(env->mlx, line,
		&env->text[nb_line]->width, &env->text[nb_line]->height);
	env->text[nb_line]->data->addr =
		mlx_get_data_addr(env->text[nb_line]->img,
			&env->text[nb_line]->data->bpp,
			&env->text[nb_line]->data->sl,
			&env->text[nb_line]->data->end);
}

void	ft_load_text(t_env *env)
{
	char	*line;
	int		nb_line;
	int		fd;

	line = NULL;
	if ((fd = open("./text.txt", O_RDONLY)) > 2)
	{
		nb_line = ft_count_line(fd, line);
		env->text = (t_text**)malloc(sizeof(t_text*) * (nb_line + 1));
		env->text[nb_line] = NULL;
	}
	close(fd);
	if ((fd = open("./text.txt", O_RDONLY)) > 2)
	{
		nb_line = 0;
		while (get_next_line(fd, &line) > 0)
		{
			ft_set_text(env, line, nb_line++);
			free(line);
		}
	}
	close(fd);
	free(line);
}
