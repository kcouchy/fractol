/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:41 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/09 15:13:26 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	int		i;
	double	temp;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offsetx;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offsety;
	while (i < fractal->div_thresh && (fractal->zx * fractal->zx
			+ fractal->zy * fractal->zy < __DBL_MAX__))
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

int	ft_build_julia(t_fractal *fractal, double cx, double cy)
{
	int		i;
	double	temp;

	i = 0;
	fractal->zx = (fractal->x / fractal->zoom) + fractal->offsetx;
	fractal->zy = (fractal->y / fractal->zoom) + fractal->offsety;
	fractal->cx = cx;
	fractal->cy = cy;
	while (i < fractal->div_thresh && (fractal->zx * fractal->zx
			+ fractal->zy * fractal->zy < __DBL_MAX__))
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
			fractal->y++;
		}
		fractal->y = 0;
		fractal->x++;
	}
	mlx_put_image_to_window(fractal->p_mlx, fractal->p_window,
		fractal->p_image, 0, 0);
	return (0);
}
