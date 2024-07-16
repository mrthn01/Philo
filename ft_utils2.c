/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:39:47 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/16 14:00:57 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		write(2, "malloc() error\n", 16);
	return (res);
}

// Improved version of sleep function
long	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}

void	write_status(t_philo *philo, long id,char *str)
{
	long	time;

	pthread_mutex_lock(philo->write_mutex);
	time = get_current_time() - philo->start_time;
	if (!is_dead(philo))
		printf("%ld %ld %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_mutex);
}

void	close_all(char *str, t_table *table)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	free(table->philos);
	free(table->forks);
}
