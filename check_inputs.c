/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:14:33 by kcouchma          #+#    #+#             */
/*   Updated: 2024/01/09 13:52:20 by kcouchma         ###   ########.fr       */
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
		k = 0;
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

int	ft_atod(t_fractal *fractal, int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	double	integer;
	double	fraction;
	double	num;
	int		is_neg;

	i = 2;
	while (i < argc)
	{
		j = 0;
		k = 0;
		integer = 0.;
		fraction = 0.;
		is_neg = 1;
		if (argv[i][j] == '-' || argv[i][j] == '+')
		{
			if (argv[i][j] == '-')
				is_neg = -1;
			j++;
		}
		while (argv[i][j] != '.' && argv[i][j])
		{
			integer = (integer * 10.) + (argv[i][j] - '0');
			j++;
		}
		if (argv[i][j] == '.')
			j++;
		while (argv[i][j])
		{
			fraction = (fraction * 10.) + (argv[i][j] - '0');
			k++;
			j++;
		}
		while (k-- > 0)
			fraction = fraction / 10.;
		num = integer + fraction;
		if (is_neg == -1)
			num = -num;
		if (i == 2)
			fractal->cx = num;
		if (i == 3)
			fractal->cy = num;
		i++;
	}
	return (0);
}

// int	ft_find_dec(char *buffer)
// {
// 	int	i;

// 	i = 0;
// 	while (buffer[i])
// 	{
// 		if (buffer[i] == '.')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// int	ft_atod(t_fractal *fractal, int argc, char **argv)
// {
// 	int		i;
// 	char	*pos_dec;
// 	int		integer;
// 	int		fraction;
// 	char	*inte;
// 	char	*frac;

// 	i = 2;
// 	while (i < argc)
// 	{
// 		pos_dec = ft_find_dec(argv[i]);
// 		if (pos_dec == -1)
// 		{
// 			integer = ftps_atoi(argv[i]);
// 			fraction = 0;
// 		}
// 		else
// 		{
// 			inte = ft_substr(char const *s, unsigned int start, size_t len)
// 			integer = 
// 		}
// // Allocates (with malloc(3)) and returns a substring from the
// //  * string `str`. The substring begins at index `start` and is of maximum
// //  * size `len`.
// // 		*ft_substr(char const *s, unsigned int start, size_t len)

// // Returns a pointer to the first occurence of `c` in `str` if it exists,
// //  * `NULL` otherwise.
// // 		char	*ft_strchr(const char *s, int c)

// 		integer = ftps_atoi(argv[i]);
// 		fraction = ftps_atoi(argv[i]);
// 		if (integer == -2147483649 || fraction == -2147483649)
// 			return (1);
// 		else if (i == 3)
// 			fractal->cx = integer + (10 to the power of strlen fraction * fraction
// 		else if (i == 4)
// 			fractal->cx = integer + (10 to the power of strlen fraction * fraction
// 		i++;
// 	}
// 	return (0);
// }

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
	return (0);
}

// int	ft_checkinputs(int argc, char **argv)
// {
// 	int		i;
// 	int		num_nums;

// 	num_nums = 0;
// 	if (argc != 2 && argc != 4)
// 		return (1);
// 	if ((ft_strncmp(argv[1], "Mandelbrot", 11) != 0) &&
// 			(ft_strncmp(argv[1], "Julia", 6) != 0))
// 		return (1);
// 	if (argc > 2 && (ft_strncmp(argv[1], "Julia", 6) != 0))
// 		return (1);
// 	if (is_not_num(argc, argv) == 1)
// 		return (1);
// 	i = 2;
// 	while (i < argc)
// 	{
// 		if (ftps_atoi(argv[i]) == -2147483649)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
