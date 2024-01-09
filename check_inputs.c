/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:14:33 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/09 16:27:13 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_not_num(int argc, char **argv)
{
	int	i;
	int	j;
	int	k;

	i = 2;
	k = 0;
	while (i < argc)
	{
		j = 0;
		k = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] == '.')
				k++;
			else if (argv[i][j] < '0' || argv[i][j] > '9' || k > 1)
				return (1);
			j++;
		}
		if (j == 0)
			return (1);
		i++;
	}
	return (0);
}

double	ftps_atoi(char **argv, int fract)
{
	double	num;
	int		i;

	num = 0.;
	i = 0;
	while (**argv && **argv != '.')
	{
		num *= 10.;
		num += **argv - '0';
		(*argv)++;
		i++;
	}
	if (fract == 1)
	{
		while (i-- > 0)
			num = num / 10.;
	}
	if (num <= 2147483647 && num >= -2147483648)
		return (num);
	return (-2147483649);
}

double	ft_atod1(char *argv)
{
	double	integer;
	double	fraction;
	int		is_neg;

	integer = 0.;
	fraction = 0.;
	is_neg = -(2 * (*argv == '-') - 1);
	if (*argv == '-' || *argv == '+')
		argv++;
	integer = ftps_atoi(&argv, 0);
	if (integer == -2147483649)
		return (-2147483649);
	if (*argv == '.')
		argv++;
	fraction = ftps_atoi(&argv, 1);
	if (fraction == -2147483649)
		return (-2147483649);
	return (is_neg * (integer + fraction));
}

int	ft_atod(t_fractal *fractal, int argc, char **argv)
{
	int		i;
	double	num;

	i = 2;
	while (i < argc)
	{
		num = ft_atod1(argv[i]);
		if (num == -2147483649)
			return (1);
		if (i == 2)
			fractal->cx = num;
		if (i == 3)
			fractal->cy = num;
		i++;
	}
	return (0);
}

// int	ft_atod(t_fractal *fractal, int argc, char **argv)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	double	integer;
// 	double	fraction;
// 	double	num;
// 	int		is_neg;

// 	i = 2;
// 	while (i < argc)
// 	{
// 		j = 0;
// 		k = 0;
// 		integer = 0.;
// 		fraction = 0.;
// 		is_neg = 1;
// 		if (argv[i][j] == '-' || argv[i][j] == '+')
// 		{
// 			if (argv[i][j] == '-')
// 				is_neg = -1;
// 			j++;
// 		}
// 		while (argv[i][j] != '.' && argv[i][j])
// 		{
// 			integer = (integer * 10.) + (argv[i][j] - '0');
// 			j++;
// 		}
// 		if (argv[i][j] == '.')
// 			j++;
// 		while (argv[i][j])
// 		{
// 			fraction = (fraction * 10.) + (argv[i][j] - '0');
// 			k++;
// 			j++;
// 		}
// 		while (k-- > 0)
// 			fraction = fraction / 10.;
// 		num = integer + fraction;
// 		if (is_neg == -1)
// 			num = -num;
// 		if (i == 2)
// 			fractal->cx = num;
// 		if (i == 3)
// 			fractal->cy = num;
// 		i++;
// 	}
// 	return (0);
// }

int	ft_checkinputs(int argc, char **argv)
{
	int		num_nums;

	num_nums = 0;
	if (argc != 2 && argc != 4)
		return (1);
	if ((ft_strncmp(argv[1], "Mandelbrot", 11) != 0)
		&& (ft_strncmp(argv[1], "Julia", 6) != 0))
		return (1);
	if (argc > 2 && (ft_strncmp(argv[1], "Julia", 6) != 0))
		return (1);
	if (is_not_num(argc, argv) == 1)
		return (1);
	return (0);
}
