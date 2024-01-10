/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:30:29 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/10 15:16:48 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/

# include <stdlib.h>		/*malloc/free/calloc && exit*/
# include <unistd.h>		/*write*/
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

/**
 * @brief Atod episode III - atoi with extra sauce (thank you norminette)
 * Basically an atoi, with an extra step in the case of fract == 1.
 * In this case, the double created is divided by 10 ^ its length using the i
 * variable to track the number of digits. This creates the fraction part of 
 * the double (the part to the right of the decimal point).
 * @param argv input argument sent from ft_atod1 ('integer' or 'fraction' part)
 * @param fract if integer then 0, if fraction then 1 (to run division cycle)
 * @return double the integer or fraction requested by ft_atod1
 */
double	ft_atod2(char **argv, int fract);

/**
 * @brief Atod episode II - the search for negs (thank you norminette)
 * In this sub-function, each argument is checked to see if it's negative or 
 * positive, then stripped of the '-' or '+'. The string before the decimal (if
 * present) if transferred using a modified atoi (ft_atd2) into the double 
 * 'integer'. The decimal (if present) is then skipped and any remaining digits
 * sent through the atoi into the double 'fraction'. The two are then added 
 * together to create the output double.
 * @param argv input argument sent from ft_atod.
 * @return double constructed from the char * input.
 */
double	ft_atod1(char *argv);

/**
 * @brief Atod episode I - return of the loops (thank you norminette)
 * This function (and the two subfunctions called therein) transform the input
 * char * args into doubles, and put them into the fractal structure (cx & cy).
 * Runs a loop through the input arguments (argv), starting from the third one.
 * Given the structure of this program, this function runs only in the case 
 * where the fractal to be constructed is 'Julia', and where there are only 
 * two extra input arguments (argv[2] and argv[3]).
 * @param fractal The fractal structure
 * @param argc input
 * @param argv input
 * @return int 1 if any of the arguments are outside of int limits, 0 if ok.
 */
int		ft_atod(t_fractal *fractal, int argc, char **argv);

/******************************************************************************/
/* build.c                                                                    */
/******************************************************************************/

/**
 * @brief Called by the fractal building functions to add colour codes to the 
 * pixels of the image (at fractal->p_p_image) based on i. 
 * If i = div_thresh, then the set was for our purposes in an infinite loop, 
 * and is coloured in black (0). Otherwise, it will set a colour based on 
 * i * fractal->colour, set in ft_set_struct2.
 * @param fractal the fractal structure
 * @param x x coordinate of the pixel to apply colour to in the image
 * @param y y coordinate of the pixel to apply colour to in the image
 * @param i the number of reps in the loop to calculate divergence (i).
 */
void	ft_colour_pixel(t_fractal *fractal, int x, int y, int i);

/**
 * @brief Runs the mandelbrot equation one pixel at a time (Z^2 + c). 
 * Z (zx, zy) starts at 0, C (cx, cy) are the pixel coordinates (taking into
 * account any pixel offset or zoom).
 * In case of a divergent result, will escape the loop once the limit DBL_MAX 
 * has been reached, then will colour the pixels in function of the number of 
 * passages taken to escape the loop (i).
 * In case of an infinite loop, the loop will break once i reaches div_thresh.
 * This is set in the function ft_set_struct1 to optimise calculation time and
 * fractal detail (around 100).
 * @param fractal the fractal structure
 */
void	ft_build_mandelbrot(t_fractal *fractal);

/**
 * @brief Runs the julia equation one pixel at a time (Z^2 + c). 
 * C (cx, cy) starts by default at 0.4 0.4 as set in ft_set_struct2, or using 
 * the values given by the user input. Z (zx, zy) are the pixel coordinates 
 * (taking into account any pixel offset or zoom).
 * @param fractal the fractal structure
 */
void	ft_build_julia(t_fractal *fractal);

/**
 * @brief Runs the burning ship equation one pixel at a time 
 * ((abs)Z^2 + (abs)c). Basically, is the mandelbrot but not Z and C are 
 * limited to non-negative (absolute) values.
 * Z (zx, zy) starts at 0, C (cx, cy) are the pixel coordinates (taking into
 * account any pixel offset or zoom).
 * @param fractal the fractal structure
 */
void	ft_build_ship(t_fractal *fractal);

/**
 * @brief Checks the structure to extract the fractal type to build. Using a 
 * raster pattern, fills in the each of the image pixels using the respective
 * fractal calculations.
 * @param fractal the fractal structure
 */
void	ft_build(t_fractal *fractal);

/******************************************************************************/
/* hooks.c                                                                    */
/******************************************************************************/

/**
 * @brief Called by the mlx_hook function (in main) to handle a mouse click on
 * the close button in the top right of the window.
 * Calls ft_free function to kill and free everything, then exits the mlx_loop.
 * @param fractal the fractal structure.
 * @return int return (0) because mlx_hook wants an int return.
 */
int		ft_close(t_fractal *fractal);

/**
 * @brief Changes the pixel offsets stored at fractal->offsetx by a set value
 * in response to the arrow keys. Takes into account the fractal->zoom.
 * @param fractal 
 * @param keycode 
 */
void	ft_move(t_fractal *fractal, int keycode);

/**
 * @brief Function called by the mlx_key_hook function (uses X11 aliases)
 * Calls the ft_free function and exit the mlx_loop if escape key is pressed.
 * Calla the ft_move function to change pixel offsets if the arrow keys
 * are used (moves the image in the window).
 * @param keycode Key pressed (activates on key release).
 * @param fractal the fractal structure.
 * @return int return (0) because mlx_key_hook wants an int return.
 */
int		ft_key_hook(int keycode, t_fractal *fractal);

/**
 * @brief Changes the value stored at fractal->zoom, and changes the pixel 
 * offset values (stored at fractal->offsetx/y) to the position of the mouse 
 * at the time of the click to recenter the zoomed image.
 * The zoom factor is set at 1.2.
 * @param button The mouse button used (4 = scroll up/zoom in, 5 = down/out)
 * @param x x position of mouse at the time of the button use.
 * @param y y position of mouse at the time of the button use.
 * @param fractal the fractal structure.
 */
void	ft_zoom(int button, int x, int y, t_fractal *fractal);

/**
 * @brief Function called by the mlx_mouse_hook function
 * Calls the zoom function if the scroll wheel is used.
 * Changes the fractal colour calculation and redraws the fractal if the left
 * or right mouse button is clicked.
 * @param button Mouse button used.
 * @param x x position of mouse at the time of the button use.
 * @param y y position of mouse at the time of the button use.
 * @param fractal the fractal structure.
 * @return int return (0) because mlx_mouse_hook wants an int return.
 */
int		ft_mouse_hook(int button, int x, int y, t_fractal *fractal);

/******************************************************************************/
/* fractol.c                                                                  */
/******************************************************************************/

/**
 * @brief Error message handling.
 * Type 1 - input error : the input doesn't correspond to the expected values.
 * Type 2 - the malloc to create the fractal structure failed.
 * Type 3 - there's a failure somewhere in Minilibx (malloc failures when 
 * creating plx or image array).
 * @param type The error type to display.
 * @param fractal the fractal structure (free in case of type 3 failure).
 * @return int return (1)
 */
int		ft_error(int type, t_fractal *fractal);

/**
 * @brief Handles a closure, makes sure everything is correctly freed.
 * Runs the mlx destroy functions mlx_destroy_image, mlx_destroy_window, 
 * mlx_destroy_display. Then frees p_mlx, and finally the fractal structure. * 
 * @param fractal the fractal structure (contains all the pointers necessary)
 */
void	ft_free(t_fractal *fractal);

/**
 * @brief Sets the parts of the fractal structure that don't call external 
 * functions or require mallocs.
 * Will set the default offsets/zooms for the initial displays of Mandelbrot 
 * and Burningship fractals.
 * @param fractal the fractal structure to set
 * @param argv input char * for the fractal/window name
 * @return int 
 */
void	ft_set_struct1(t_fractal *fractal, char **argv);

/**
 * @brief Sets the parts of the fractal structure that call external 
 * functions or require mallocs.
 * Will set the cx/cy values at 0 for Mandelbrot/BurningShip, for Julia
 * will set using user inputs (calls ft_atod), or default as 0.4 0.4.
 * Calls mlx_init, mlx_new_window, mlx_new_image, and mlx_get_data_addr
 * and adds outputs to the respective fractal structure variables.
 * @param fractal the fractal structure to set
 * @param argc input
 * @param argv input
 * @return int 1 to handle malloc failures, 0 if all goes well.
 */
int		ft_set_struct2(t_fractal *fractal, int argc, char **argv);

/**
 * @brief Main function to check the inputs (ft_checkinputs), malloc the 
 * fractal structure and initialise the values (ft_set_struct1 and 2).
 * Then runs the minilibx functions for mouse and key hooks :
 * mlx_key_hook, mlx_mouse_hook, mlx_hook (close button).
 * ft_build to build the fractal images.
 * mlx_loop to wait for user inputs.
 * ft_free to destroy everything and free correctly before end of program
 * @param argc input
 * @param argv input
 * @return int 1 if error occured, 0 if all went well.
 */
int		main(int argc, char **argv);

#endif