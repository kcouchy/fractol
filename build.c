/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/08 18:17:25 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_colour_pixel(t_fractal *fractal, int x, int y, int i)
{
	int	*temp;
	int	pixel;

	i = (i * fractal->colour);
	temp = fractal->p_p_image;
	pixel = (y * fractal->linesize / 4) + x;
	temp[pixel] = i;
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
	ft_colour_pixel(fractal, fractal->x, fractal->y, fractal->div_thresh - i);
	// if (i == fractal->div_thresh)
	// 	ft_colour_pixel(fractal, fractal->x, fractal->y, 0);
	// else
	// 	ft_colour_pixel(fractal, fractal->x, fractal->y, i);
	return (0);
}

// void	ft_colour_pixel(t_fractal *fractal, int x, int y, int colour)
// {
	// int	*temp;
	// int	pixel;
	// // int	i_reset;
	
	// // i_reset = i;
	// // if (i != 0)
	// // {
	// 	i = (i * fractal->colour);
	// // 	// i = ((i * 1000000000) / fractal->zoom);
	// 	// if (i < 0)
	// 	// 	i = -i;
	// 	// if (i < 200)
	// 	// 	i *= 600000;
	// // }
	// temp = fractal->p_p_image;
	// pixel = (y * fractal->linesize / 4) + x;
	// temp[pixel] = i;
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
// 	// printf("%.15f\n", (i * 100000000) / fractal->zoom);
// 	return (0);
// }

int	ft_build_julia(t_fractal *fractal, double cx, double cy)
{
	int	i;
	double temp;

	i = 0;
	fractal->zx = (fractal->x / fractal->zoom) + fractal->offsetx;
	fractal->zy = (fractal->y / fractal->zoom) + fractal->offsety;
	fractal->cx = cx;
	fractal->cy = cy;
	if (fractal->cx == 0 && fractal->cy == 0)
	{
		fractal->cx = 0.4;
		fractal->cy = 0.4;
	}
	while (i < fractal->div_thresh && (fractal->zx * fractal->zx +
			fractal->zy * fractal->zy < __DBL_MAX__))
	{
		temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2. * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = temp;
		i++;
	}
	ft_colour_pixel(fractal, fractal->x, fractal->y, fractal->div_thresh - i);
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
				ft_build_julia(fractal, fractal->cx, fractal->cy);
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
