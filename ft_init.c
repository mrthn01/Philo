/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:33:38 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/11 00:02:12 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->philo_num;
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
	table->philos->philo_num = ft_atol(argv[1]);
	table->philos->time_to_die = ft_atol(argv[2]);
	table->philos->time_to_eat = ft_atol(argv[3]);
	table->philos->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->philos->number_of_meals = ft_atol(argv[5]);
	else
		table->philos->number_of_meals = -1;
}

void	table_init(t_table *table)
{
	int	i;

	i = 0;
	table->dead_flag = 0;
	table->philos = ft_malloc(sizeof(t_philo) * table->philos->philo_num);
	pthread_mutex_init(&table->dead_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	table->fork = ft_malloc(sizeof(t_fork) * table->philos->philo_num);
	while (i < table->philos->philo_num)
	{
		pthread_mutex_init(&table->fork[i].fork, NULL);
		table->fork[i].fork_id = i;
	}
}

void	philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->philos->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meal_counter = 0;
		philo->start_time = get_current_time();
		philo->last_meal_time = get_current_time();
		philo->dead_mutex = &table->dead_mutex;
		philo->write_mutex = &table->write_mutex;
		philo->meal_mutex = &table->meal_mutex;
		philo->table = table;
		assign_forks(philo, table->fork, i);
	}
}

void	data_init(t_table *table, t_philo *philo, char **argv)
{
	arg_init(table, argv);
	table_init(table);
	philo_init(table);
}
