/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:46:32 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/08 17:04:16 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_close(t_fractal *fractal)
{
	ft_free(fractal);
	exit (1);
}

int	ft_key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == XK_Escape)
	{
		ft_free(fractal);
		exit (1);
	}
	return (0);
}
void ft_zoom(int button, int x,int y, t_fractal *fractal)
{
	double	zoom;

	zoom = 1.2;
	if (button == 4)
	{
		fractal->offsetx = (x / fractal->zoom + fractal->offsetx) -
				(x / (fractal->zoom * zoom));
		fractal->offsety = (y / fractal->zoom + fractal->offsety) -
				(y / (fractal->zoom * zoom));
		fractal->zoom *= zoom;
	}
	else if (button == 5)
	{
		fractal->offsetx = (x / fractal->zoom + fractal->offsetx) -
				(x / (fractal->zoom / zoom));
		fractal->offsety = (y / fractal->zoom + fractal->offsety) -
				(y / (fractal->zoom / zoom));
		fractal->zoom /= zoom;
	}
	else
		return ;
}

int	ft_mouse_hook(int button, int x,int y, t_fractal *fractal)
{
	if (button == 4 || button == 5)
	{
		ft_zoom(button, x, y, fractal);
		ft_build(fractal);
	}
	if (button == 1)
		ft_printf("x: %d, y: %d, colour: %d\n", x, y);
	return (0);
}

// 	// Left click: 1
// 	// Right click: 2
// 	// Middle click: 3
// 	// Scroll up: 4
// 	// Scroll down : 5
// **   expose_hook(void *param);
// **   loop_hook(void *param);