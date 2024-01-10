/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:46:32 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/10 13:42:26 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_close(t_fractal *fractal)
{
	ft_free(fractal);
	exit (1);
}

void	ft_move(t_fractal *fractal, int keycode)
{
	if (keycode == XK_Left)
		fractal->offsetx -= 20 / fractal->zoom;
	if (keycode == XK_Right)
		fractal->offsetx += 20 / fractal->zoom;
	if (keycode == XK_Up)
		fractal->offsety -= 20 / fractal->zoom;
	if (keycode == XK_Down)
		fractal->offsety += 20 / fractal->zoom;
}

int	ft_key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == XK_Escape)
	{
		ft_free(fractal);
		exit (1);
	}
	if (keycode == XK_Left || keycode == XK_Right || keycode == XK_Up
		|| keycode == XK_Down)
	{
		ft_move(fractal, keycode);
		ft_build(fractal);
	}
	return (0);
}

void	ft_zoom(int button, int x, int y, t_fractal *fractal)
{
	double	zoom;

	zoom = 1.2;
	if (button == 4)
	{
		fractal->offsetx = (x / fractal->zoom + fractal->offsetx)
			- (x / (fractal->zoom * zoom));
		fractal->offsety = (y / fractal->zoom + fractal->offsety)
			- (y / (fractal->zoom * zoom));
		fractal->zoom *= zoom;
	}
	else if (button == 5)
	{
		fractal->offsetx = (x / fractal->zoom + fractal->offsetx)
			- (x / (fractal->zoom / zoom));
		fractal->offsety = (y / fractal->zoom + fractal->offsety)
			- (y / (fractal->zoom / zoom));
		fractal->zoom /= zoom;
	}
}

int	ft_mouse_hook(int button, int x, int y, t_fractal *fractal)
{
	if (button == 4 || button == 5)
	{
		ft_zoom(button, x, y, fractal);
		ft_build(fractal);
	}
	if (button == 1)
	{
		fractal->colour += 100;
		ft_build(fractal);
	}
	if (button == 3)
	{
		fractal->colour -= 100;
		ft_build(fractal);
	}
	return (0);
}
