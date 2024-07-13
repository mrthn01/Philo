/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:39:47 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/13 13:51:10 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return ;
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	write_status(t_philo *philo, t_status status)
{
	long	elapsed;

	elapsed = get_current_time();
	pthread_mutex_lock(&philo->write_mutex);
	if (status == TAKE_RIGHT_FORK)
		printf("%-6ld %d has taken right fork\n", elapsed, philo->id);
	else if (status == TAKE_LEFT_FORK)
		printf("%-6ld %d has taken left fork\n", elapsed, philo->id);
	else if (status == SLEEPING)
		printf("%-6ld %d is sleeing\n", elapsed, philo->id);
	else if (status == EATING)
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == THINKING)
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d is dead\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->write_mutex);
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
	i = 0;
	free(table->philos);
	free(table->forks);
}
