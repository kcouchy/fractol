/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:15:47 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/10 14:01:57 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_error(int type, t_fractal *fractal)
{
	if (type == 1)
	{
		ft_printf("\nInput error, choose a fractal:\n");
		ft_printf(" 1. Mandelbrot\n	./fractol Mandelbrot \n");
		ft_printf(" 2. Julia (option with 2 starting parameters).\n");
		ft_printf("	./fractol Julia\n	./fractol Julia 0.3 0\n");
		ft_printf(" 3. Burning Ship\n	./fractol BurningShip \n\n");
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

void	ft_set_struct1(t_fractal *fractal, char **argv)
{
	fractal->name = argv[1];
	fractal->x = 0;
	fractal->y = 0;
	fractal->zx = 0;
	fractal->zy = 0;
	fractal->zoom = 300;
	fractal->offsetx = - ((SIZEW / 2) / fractal->zoom);
	fractal->offsety = - ((SIZEH / 2) / fractal->zoom);
	if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
	{
		fractal->offsetx = - (((SIZEW / 2) + 200) / fractal->zoom);
		fractal->offsety = - ((SIZEH / 2) / fractal->zoom);
	}
	if (ft_strncmp(argv[1], "BurningShip", 12) == 0)
	{
		fractal->zoom = 1000;
		fractal->offsetx = - (((SIZEW / 2) + 1500) / fractal->zoom);
		fractal->offsety = - ((SIZEH / 2) / fractal->zoom);
	}
	fractal->colour = 5000;
	fractal->div_thresh = 100;
}

int	ft_set_struct2(t_fractal *fractal, int argc, char **argv)
{
	fractal->cx = 0;
	fractal->cy = 0;
	if (argc == 4 && (ft_strncmp(argv[1], "Julia", 6) == 0))
	{
		if (ft_atod(fractal, argc, argv) == 1)
			return (ft_error(1, fractal));
	}
	else if (ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		fractal->cx = 0.4;
		fractal->cy = 0.4;
	}
	fractal->p_mlx = mlx_init();
	if (!fractal->p_mlx)
		return (ft_error(3, fractal));
	fractal->p_window = mlx_new_window(fractal->p_mlx, SIZEW, SIZEH,
			fractal->name);
	if (!fractal->p_window)
		return (free(fractal->p_mlx), ft_error(3, fractal));
	fractal->p_image = mlx_new_image(fractal->p_mlx, SIZEW, SIZEH);
	fractal->p_p_image = mlx_get_data_addr(fractal->p_image,
			&fractal->pixelbits, &fractal->linesize, &fractal->endian);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	fractal = NULL;
	if (ft_checkinputs(argc, argv) == 1)
		return (ft_error(1, fractal));
	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (ft_error(2, fractal));
	ft_set_struct1(fractal, argv);
	if (ft_set_struct2(fractal, argc, argv) == 1)
		return (free(fractal), 1);
	mlx_key_hook(fractal->p_window, ft_key_hook, fractal);
	mlx_mouse_hook(fractal->p_window, ft_mouse_hook, fractal);
	mlx_hook(fractal->p_window, 17, 1L << 17, ft_close, fractal);
	ft_build(fractal);
	mlx_loop(fractal->p_mlx);
	ft_free(fractal);
	return (0);
}
