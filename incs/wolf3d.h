/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 10:21:59 by kdezaphi          #+#    #+#             */
/*   Updated: 2015/02/09 14:09:42 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIDTH 768
# define HEIGHT 576
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)

# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>
# include <mlx.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"

typedef struct	s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}				t_player;

typedef struct	s_ray
{
	double	poscam;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
}				t_ray;

typedef struct	s_data
{
	void	*mlx;
	int		bpp;
	int		sl;
	int		end;
	char	*addr;
}				t_data;

typedef struct	s_text
{
	void	*img;
	double	wallx;
	double	wally;
	double	floorx;
	double	floory;
	int		width;
	int		height;
	int		texx;
	int		texy;
	double	d;
	t_data	*data;
}				t_text;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	int			**map;
	int			move[4];
	clock_t		time;
	clock_t		oldtime;
	double		frametime;
	double		zbuf[WIDTH];
	t_data		*data;
	t_player	*player;
	t_text		**text;
	t_ray		*ray;
}				t_env;

typedef struct	s_calc
{
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		drawstart;
	int		drawstop;
	int		hit;
	int		side;
	int		lineh;
	double	wallx;
	double	walldist;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
}				t_calc;

typedef union	u_color
{
	char	oct[4];
	int		cv;
}				t_color;

int				ft_count_line(int fd, char *line);
void			ft_init(t_env *env);
int				ft_consline(t_env *env, char *line, int nb_line);
int				ft_consmap(t_env *env);
void			ft_put_pixel_to_image(int x, int y, t_env *env, int color);
int				ft_get_pixel_color(int x, int y, t_data *data);
void			ft_calc_ray(t_env *env, t_calc *calc, int x);
void			ft_set_step(t_env *env, t_calc *calc);
void			ft_calc_dist(t_env *env, t_calc *calc);
void			ft_calc_draw(t_env *env, t_calc *calc);
void			ft_calc_wall(t_env *env, t_calc *calc, int numtext);
void			ft_trace_wall(t_env *env, t_calc *calc, int numtext, int x);
void			ft_calc_floor(t_env *env, t_calc *calc);
void			ft_trace_floor(t_env *env, t_calc *calc, int x);
void			ft_trace_column(t_env *env, t_calc *calc, int x);
char			*ft_calc_frametime(t_env *env);
void			ft_player_move(int up, t_env *env);
void			ft_player_rota(double rota, t_env *env);
void			ft_check_move(t_env *env);
int				expose_hook(t_env *env);
void			ft_delete(t_env *env);
int				key_release_hook(int keycode, t_env *env);
int				key_press_hook(int keycode, t_env *env);
void			ft_set_text(t_env *env, char *line, int nb_line);
void			ft_load_text(t_env *env);
void			ft_free_env(t_env *env);

#endif
