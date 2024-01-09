/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:30:29 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/09 18:16:42 by kcouchma         ###   ########.fr       */
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
# include <math.h>			/*fabs*/

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
	double	zoom;
	double	offsetx;
	double	offsety;
	int		colour;
	int		div_thresh;
}			t_fractal;

/******************************************************************************/
/* check_inputs.c                                                             */
/******************************************************************************/

/**
 * @brief Checks the inputs: can start with either 1 '-' or '+'. 
 * May contain up to 1 decimal point.
 * The rest of the word must consist of digits 0-9.
 * @param argc input
 * @param argv input
 * @return int returns 0 if all argv are fine, otherwise 1.
 */
int		is_not_num(int argc, char **argv);

/**
 * @brief Runs the above check function and checks input validity (names).
 * @param argc input
 * @param argv input
 * @return int returns 0 if all argv are fine, otherwise 1.
 */
int		ft_checkinputs(int argc, char **argv);

double	ft_atod2(char **argv, int fract);

double	ft_atod1(char *argv);

int		ft_atod(t_fractal *fractal, int argc, char **argv);


/******************************************************************************/
/* build.c                                                                    */
/******************************************************************************/

int		ft_build_mandelbrot(t_fractal *fractal);

int		ft_build_julia(t_fractal *fractal, double cx, double cy);

int 	ft_build_ship(t_fractal *fractal);

int 	ft_build(t_fractal *fractal);

/******************************************************************************/
/* hooks.c                                                                    */
/******************************************************************************/

int		ft_close(t_fractal *fractal);

void	ft_move(t_fractal *fractal, int keycode);

void	ft_zoom(int button, int x, int y, t_fractal *fractal);

int		ft_key_hook(int keycode, t_fractal *fractal);

int		ft_mouse_hook(int button, int x,int y, t_fractal *fractal);

/******************************************************************************/
/* fractol.c                                                                  */
/******************************************************************************/

int		ft_error(int type, t_fractal *fractal);

void	ft_free(t_fractal *fractal);

int		ft_set_struct1(t_fractal *fractal, char **argv);
int		ft_set_struct2(t_fractal *fractal, int argc, char **argv);

int		main(int argc, char **argv);

#endif