/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:30:29 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/08 17:00:56 by kcouchma         ###   ########.fr       */
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
 * @brief checks the inputs to see if they contain only numbers, can start with 
 * either '-' or '+'.
 * @param argc input
 * @param argv input
 * @return int returns 0 if all argv are fine, otherwise 
 * error() (Prints "Error\n" to the standard output and returns 1).
 */
int		is_not_num(int argc, char **argv);

/**
 * @brief checks the inputs one at a time to see if they are a valid int.
 * @param argv 
 * @return long returns number is a valid int, otherwise returns -2147483649 
 * (beyond min int so invalid).
 */
long	ftps_atoi(char *argv);

/**
 * @brief Runs all of the above check functions to make sure the input is valid.
 * @param argc input
 * @param argv input
 * @return int returns 0 if all argv are fine, otherwise 1.
 */
int		ft_checkinputs(int argc, char **argv);


/******************************************************************************/
/* build.c                                                                    */
/******************************************************************************/

int		ft_build_mandelbrot(t_fractal *fractal);

int		ft_build_julia(t_fractal *fractal, double cx, double cy);

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

int		ft_set_struct(t_fractal *fractal, int argc, char **argv);

int		main(int argc, char **argv);

#endif