/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:15:47 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/05 17:01:02 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_error(int type, t_fractal *fractal)
{
	if (type == 1)
	{
		ft_printf("Input error, choose a fractal:\n Mandelbrot\n Julia\n");
		ft_printf("For Julia, you can also input starting coordinates");
		ft_printf("(within int limits) for X and Y\n");
	}
	else if (type == 2)
	{
		ft_printf("Malloc failure, please retry");
	}
	else if (type == 3)
	{
		ft_printf("Minilibx failure, please retry");
		free(fractal);
	}
	return (1);
}

void	ft_free(t_fractal *fractal)
{
	mlx_destroy_image(fractal->p_mlx, fractal->p_image);
	mlx_destroy_window(fractal->p_mlx, fractal->p_window);
	mlx_destroy_display(fractal->p_mlx);
	free(fractal->p_mlx);
	free(fractal);
}

int	ft_set_struct(t_fractal *fractal, char **argv)
{
	fractal->name = argv[1];
	fractal->p_mlx = mlx_init();
	if (!fractal->p_mlx)
		return (ft_error(3, fractal));
	fractal->p_window = mlx_new_window(fractal->p_mlx, SIZEW, SIZEH,
			fractal->name);
	if (!fractal->p_window)
	{
		free(fractal->p_mlx);
		return (ft_error(3, fractal));
	}
	fractal->p_image = mlx_new_image(fractal->p_mlx, SIZEW, SIZEH);
	fractal->p_p_image = mlx_get_data_addr(fractal->p_image,
			&fractal->pixelbits, &fractal->linesize, &fractal->endian);
	fractal->x = 0;
	fractal->y = 0;
	fractal->zx = 0;
	fractal->zy = 0;
	fractal->cx = 0;
	fractal->cy = 0;
	fractal->offsetx = -2;
	fractal->offsety = -1.5;
	fractal->zoom = 300;
	fractal->div_thresh = 100;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	fractal = NULL;
	if (argc < 2) //MAY NEED TO HANDLE JULIA INPUTS AS ARGS (2 ints, then atoi, then transform to doubles somehow)
		return (ft_error(1, fractal));
	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (ft_error(2, fractal));
	if (ft_set_struct(fractal, argv) == 1)
		return (free(fractal), 1);
	mlx_key_hook(fractal->p_window, ft_key_hook, fractal);
	mlx_mouse_hook(fractal->p_window, ft_mouse_hook, fractal);
	mlx_hook(fractal->p_window, 17, 1L << 17, ft_close, fractal);
	if ((ft_strncmp(argv[1], "Mandelbrot", 11) == 0) || (ft_strncmp(argv[1],
				"Julia", 6) == 0))
		ft_build(fractal);
	else
		ft_error(1, fractal);
	mlx_loop(fractal->p_mlx);
	ft_free(fractal);
	return (0);
}
