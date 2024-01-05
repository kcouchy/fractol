/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/05 18:14:56 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_colour_pixel(t_fractal *fractal, int x, int y, int i)
{
	int	*temp;
	int	i_reset;
	
	i_reset = i;
	if (i != 0)
	{
		i = ((i * 1000000000) / fractal->zoom);
		// if (i < 0)
		// 	i = -i;
		if (i < 200)
			i *= 100000000;
	}
	temp = fractal->p_p_image;
	temp[(y * fractal->linesize / 4) + x] = i;
}

int	ft_build_mandelbrot(t_fractal *fractal)
{
	int	i;
	double temp;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offsetx;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offsety;
	while (i < fractal->div_thresh && (fractal->zx * fractal->zx +
			fractal->zy * fractal->zy < __DBL_MAX__))
	{
		temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2. * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = temp;
		i++;
	}
	if (i == fractal->div_thresh)
		ft_colour_pixel(fractal, fractal->x, fractal->y, 0);
	else
		ft_colour_pixel(fractal, fractal->x, fractal->y, i);
	return (0);
}

// void	ft_colour_pixel(t_fractal *fractal, int x, int y, int colour)
// {
// 	int	*temp;

// 	temp = fractal->p_p_image;
// 	temp[(y * fractal->linesize / 4) + x] = colour;
// }

// int	ft_build_mandelbrot(t_fractal *fractal)
// {
// 	int	i;
// 	double temp;

// 	i = 0;
// 	fractal->zx = 0.0;
// 	fractal->zy = 0.0;
// 	fractal->cx = (fractal->x / fractal->zoom) + fractal->offsetx;
// 	fractal->cy = (fractal->y / fractal->zoom) + fractal->offsety;
// 	while (i < fractal->div_thresh && (fractal->zx * fractal->zx +
// 			fractal->zy * fractal->zy < __DBL_MAX__))
// 	{
// 		temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
// 			+ fractal->cx;
// 		fractal->zy = 2. * fractal->zx * fractal->zy + fractal->cy;
// 		fractal->zx = temp;
// 		i++;
// 	}
// 	if (i == fractal->div_thresh)
// 		ft_colour_pixel(fractal, fractal->x, fractal->y, 0x000000);
// 	else
// 		ft_colour_pixel(fractal, fractal->x, fractal->y, ((i * 100000000) / fractal->zoom));
// 	printf("%.15f\n", (i * 100000000) / fractal->zoom);
// 	return (0);
// }

int	ft_build_julia(t_fractal *fractal)
{
	t_fractal	*temp;

	temp = fractal;
	return (0);
}

int	ft_build(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZEW)
	{
		while (fractal->y < SIZEH)
		{
			if (ft_strncmp(fractal->name, "Mandelbrot", 11) == 0)
				ft_build_mandelbrot(fractal);
			else if (ft_strncmp(fractal->name, "Julia", 6) == 0)
				ft_build_julia(fractal);
			// else
			// 	ft_printf("FUCK");
			fractal->y++;
		}
		fractal->y = 0;
		fractal->x++;
	}
	mlx_put_image_to_window(fractal->p_mlx, fractal->p_window, fractal->p_image, 0, 0);
	return (0);
}
