/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:30:29 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/05 17:01:30 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/

# include <stdlib.h>		/*malloc/free/calloc && exit*/
# include <unistd.h>		/*write*/
# include <fcntl.h>			/*open, close*/
# include "libft/libft.h"	/*includes my libft.h - ft_printf, getnextline*/
# include "minilibx-linux-master/mlx.h" /*includes minilibx*/
# include "X11/keysym.h"	/*includes keyboard button aliases*/
# include <math.h>
# include <pthread.h>

/******************************************************************************/
/* Defaults                                                                   */
/******************************************************************************/

# define SIZEW 900
# define SIZEH 900

/******************************************************************************/
/* Structures                                                                 */
/******************************************************************************/

typedef struct s_fractal
{
	char	*name;
	void	*p_mlx;
	void	*p_window;
	void	*p_image;
	void	*p_p_image;
	int		pixelbits;
	int		linesize;
	int		endian;
	int		x;
	int		y;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	double	offsetx;
	double	offsety;
	double	zoom;
	int		div_thresh;
}			t_fractal;

/******************************************************************************/
/* build.c                                                                    */
/******************************************************************************/

int		ft_build_mandelbrot(t_fractal *fractal);

int		ft_build_julia(t_fractal *fractal);

int 	ft_build(t_fractal *fractal);

/******************************************************************************/
/* hooks.c                                                                    */
/******************************************************************************/

int		ft_close(t_fractal *fractal);

int		ft_key_hook(int keycode, t_fractal *fractal);

int		ft_mouse_hook(int button, int x,int y, t_fractal *fractal);

/******************************************************************************/
/* fractol.c                                                                  */
/******************************************************************************/

int		ft_error(int type, t_fractal *fractal);

void	ft_free(t_fractal *fractal);

int		ft_set_struct(t_fractal *fractal, char **argv);

int		main(int argc, char **argv);

#endif