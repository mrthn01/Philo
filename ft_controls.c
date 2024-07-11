/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:50:02 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/10 23:31:15 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_digits(char *argv)
{
	while (*argv)
	{
		if (!is_digit(*argv))
			return (1);
		argv++;
	}
	return (0);
}

int	check_args(char **argv)
{
	if (ft_atol(argv[1]) <= 0 || check_arg_digits(argv[1]) == 1)
		return (ft_error("Philo numbers doesn't valid"));
	else if (ft_atol(argv[2]) <= 0 || check_arg_digits(argv[2]) == 1)
		return (ft_error("Time to die doesn't valid"));
	else if (ft_atol(argv[3]) <= 0 || check_arg_digits(argv[3]) == 1)
		return (ft_error("Time to die doesn't valid"));
	else if (ft_atol(argv[4]) <= 0 || check_arg_digits(argv[4]) == 1)
		return (ft_error("Time to die doesn't valid"));
	else if (argv[5])
	{
		if (check_arg_digits(argv[5]) == 1)
			return (ft_error("Number of limits is wrong"));
	}
	return (0);
}