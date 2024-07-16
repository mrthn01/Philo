/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:47:55 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/16 13:13:11 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	write_status(philo, philo->id, "is thinking");
}

void	sleeping(t_philo *philo)
{
	write_status(philo, philo->id, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	write_status(philo, philo->id, "has taken a fork");
	if (philo->table->philo_num == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	write_status(philo, philo->id, "has taken a fork");
	philo->meal_flag = 1;
	write_status(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meal_counter++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->time_to_eat);
	philo->meal_flag = 0;
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(philo->first_fork);
}
