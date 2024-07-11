/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:33:38 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/11 14:25:51 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int pos, long philo_nbr)
{
	philo->first_fork = &forks[(pos + 1) % philo_nbr];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[(pos + 1) % philo_nbr];
		philo->second_fork = &forks[pos];
	}
}

void	arg_init(t_table *table, char **argv)
{
	table->philo_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]);
	else
		table->number_of_meals = -1;
}

void	table_init(t_table *table)
{
	int	i;

	i = 0;
	table->dead_flag = 0;
	table->philos = ft_malloc(sizeof(t_philo) * table->philo_num);
	pthread_mutex_init(&table->dead_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	table->forks = ft_malloc(sizeof(t_fork) * table->philo_num);
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
		i++;
	}
}

void	philo_init(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meal_counter = 0;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].start_time = get_current_time();
		table->philos[i].last_meal_time = get_current_time();
		table->philos[i].write_mutex = &table->write_mutex;
		table->philos[i].meal_mutex = &table->meal_mutex;
		table->philos[i].dead_mutex = &table->dead_mutex;
		assign_forks(&table->philos[i], table->forks, i, table->philo_num);
		i++;
	}
}

void	data_init(t_table *table, t_philo *philo, char **argv)
{
	arg_init(table, argv);
	table_init(table);
	philo_init(table);
}
