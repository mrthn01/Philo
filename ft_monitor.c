/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:51:47 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/15 15:13:45 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, long time_to_die)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (get_current_time() - philo->last_meal_time >= time_to_die &&
		philo->meal_flag == 0)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

int	check_philo_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].table->philo_num)
	{
		if (philo_dead(&philo[i], philo[0].time_to_die) == 1)
		{
			pthread_mutex_lock(philo->dead_mutex);
			*philo->dead = 1;
			pthread_mutex_lock(philo->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philos_full(t_philo *philo)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philo->number_of_meals == -1)
		return (0);
	while (i < philo[0].table->philo_num)
	{
		pthread_mutex_lock(philo[i].meal_mutex);
		if (philo[i].meal_counter >= philo[i].number_of_meals)
			ate++;
		pthread_mutex_unlock(philo[i].meal_mutex);
		i++;		
	}
	if (ate == philo[0].number_of_meals)
	{
		pthread_mutex_lock(philo->dead_mutex);
		*philo->dead = 1;
		pthread_mutex_lock(philo->dead_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (check_philo_dead(philo) == 1 || philos_full(philo) == 1)
			break ;
	}
	return (data);
}