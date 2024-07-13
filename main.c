/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:33:15 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/13 13:54:10 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argc != 5 || argc != 6)
		return (ft_error("Not enough argumnets"));
	if (check_args(argv) == 1)
		return (1);
	data_init(&table, argv);
	simulation(&table);
	close_all(NULL, &table);
	return (0);
}
