/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:47:55 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/14 14:26:31 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	write_status(philo, THINKING, philo->id);
}

void	sleeping(t_philo *philo)
{
	write_status(philo, SLEEPING, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	write_status(philo, TAKE_LEFT_FORK, philo->id);
	if (philo->table->philo_num == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	write_status(philo, TAKE_RIGHT_FORK, philo->id);
	philo->meal_flag = 1;
	write_status(philo, EATING, philo->id);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meal_counter++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->time_to_eat);
	philo->meal_flag = 0;
	pthread_mutex_destroy(philo->second_fork);
	pthread_mutex_destroy(philo->first_fork);
}
