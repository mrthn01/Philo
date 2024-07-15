/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:31:02 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/15 15:05:38 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philos)
{
	pthread_mutex_lock(philos->dead_mutex);
	if (*philos->dead == 1)
	{
		pthread_mutex_unlock(philos->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(philos->dead_mutex);
	return (0);
}

void	*dinner(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo))
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (data);
}

int	simulation(t_table *table)
{
	pthread_t	waiter; // observer thread
	int			i;

	i = 0;
	if (pthread_create(&waiter, NULL, &monitor, table->philos) != 0)
		return (ft_error("Failed at creating thread"));
	while (i < table->philo_num)
	{
		if (pthread_create(&table->philos[i].th, NULL, &dinner, &table->philos[i]) != 0)
			return (ft_error("Failed at creating thred"));
		i++;
	}
	if (pthread_join(waiter, NULL) != 0)
		return (ft_error("Failed at joining thread"));
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(table->philos[i].th, NULL))
			return (ft_error("Failed at joining thread"));
		i++;
	}
	return (0);
}
