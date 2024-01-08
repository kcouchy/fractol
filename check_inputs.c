/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:14:33 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/08 18:18:48 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_not_num(int argc, char **argv)
{
	int	i;
	int	j;
	int k;

	i = 2;
	k = 0;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] == '.')
			{
				k++;
				j++;
			}
			if (argv[i][j] < '0' || argv[i][j] > '9' || k > 1)
				return (1);
			j++;
		}
		if (j == 0)
			return (1);
		i++;
	}
	return (0);
}

double	ftps_atod(char *argv)
{
	long	num;
	int		is_neg;

	num = 0;
	is_neg = 1;
	ft_printf("%d\n", num);
	if (*argv == '-' || *argv == '+')
	{
		if (*argv == '-')
			is_neg = -1;
		argv++;
	}
	if (!*argv)
		return (-2147483649);
	while (*argv)
	{
		num *= 10;
		num += *argv - '0';
		argv++;
	}
	if (is_neg == -1)
		num = -num;
	if (num <= 2147483647 && num >= -2147483648)
		return (num);
	return (-2147483649);
}

// long	ftps_atoi(char *argv)
// {
// 	long	num;
// 	int		is_neg;

// 	num = 0;
// 	is_neg = 1;
// 	ft_printf("%d\n", num);
// 	if (*argv == '-' || *argv == '+')
// 	{
// 		if (*argv == '-')
// 			is_neg = -1;
// 		argv++;
// 	}
// 	if (!*argv)
// 		return (-2147483649);
// 	while (*argv)
// 	{
// 		num *= 10;
// 		num += *argv - '0';
// 		argv++;
// 	}
// 	if (is_neg == -1)
// 		num = -num;
// 	if (num <= 2147483647 && num >= -2147483648)
// 		return (num);
// 	return (-2147483649);
// }

int	ft_checkinputs(int argc, char **argv)
{
	int		i;
	int		num_nums;

	num_nums = 0;
	if (argc != 2 && argc != 4)
		return (1);
	if ((ft_strncmp(argv[1], "Mandelbrot", 11) != 0) &&
			(ft_strncmp(argv[1], "Julia", 6) != 0))
		return (1);
	if (argc > 2 && (ft_strncmp(argv[1], "Julia", 6) != 0))
		return (1);
	if (is_not_num(argc, argv) == 1)
		return (1);
	i = 2;
	while (i < argc)
	{
		if (ftps_atoi(argv[i]) == -2147483649)
			return (1);
		i++;
	}
	return (0);
}
