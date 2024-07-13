/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:31:02 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/13 14:02:17 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*dinner(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (!is_dead(philo))
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return (data);
}

void	simulation(t_table *table)
{
	pthread_t	*waiter; // observer thread
	int			i;

	i = 0;
	if (create(&waiter, &monitor, NULL) != 0)
		return ;
	while (i < table->philo_num)
	{
		if (create(&table->philos[i].th, &dinner, &table->philos[i]) != 0)
			return ;
		i++;
	}
	if (join(waiter) != 0)
		return ;
	i = 0;
	while (i < table->philo_num)
	{
		if (join(table->philos[i].th))
			return ;
		i++;
	}
}
