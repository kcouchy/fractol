/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:15:47 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/03 16:43:02 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void	*mlx_init();
void	ft_error(int type)
{
	if (type == 1)
	{
		ft_printf("Input error, choose a fractal:\n Mandelbrot\n Julia\n");
		ft_printf("For Julia, you can also input starting parameters:\n");
		ft_printf("X and Y \n");
	}
}

void	ft_mandel()
{

}

void	ft_julia()
{

}

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_error(1);
	if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
		ft_mandel();
	else if (ft_strncmp(argv[1], "Julia", 6) == 0)
		ft_julia();
	else
		ft_error(1);
}
