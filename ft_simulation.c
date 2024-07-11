/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:31:02 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/11 19:56:05 by murathanelc      ###   ########.fr       */
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
	pthread_create(waiter, NULL, &monitor, NULL);
	while (i < table->philo_num)
	{
		pthread_create(&table->philos[i].th, NULL, &dinner, &table->philos[i]);
		i++;
	}
	pthread_join(waiter, NULL);
	i = 0;
	while (i < table->philo_num)
	{
		pthread_join(table->philos[i].th, NULL);
		i++;
	}
}
