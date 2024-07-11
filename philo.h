/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:45:45 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/10 23:58:18 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_table t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	long	fork_id;
}				t_fork;


typedef struct s_philo
{
	long	id;
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meal_counter;
	long	number_of_meals;
	long	start_time;
	long	last_meal_time;
	t_table	*table;
	t_mutex	*first_fork;
	t_mutex	*second_fork;
	t_mutex	*write_mutex;
	t_mutex	*meal_mutex;
	t_mutex	*dead_mutex;
}				t_philo;

typedef struct s_table
{
	long	dead_flag;
	t_mutex	dead_mutex; // for dead philos
	t_mutex	write_mutex; // for printing
	t_mutex	meal_mutex;
	t_fork	*fork;	// for eating
	t_philo	*philos;
}			t_table;

// Utils
size_t	ft_strlen(const char *str);
int		ft_error(char *str);
int		is_space(char c);
int		is_digit(char c);
long	ft_atol(const char *str);
void	*ft_malloc(size_t size);
long	get_current_time(void);
long	ft_usleep(size_t milliseconds);

// Controls
int	check_args_digit(char *argv);
int	check_args(char **argv);

// Initialize the data
void	inputs(t_table *table, char **argv);
void	table_init(t_table *table);
void	assign_forks(t_philo *philo, t_mutex *fork, int pos);
void	philo_init(t_table *table);
void	ft_args_init(t_table *table, char **argv);

// Dinner Simulation
void	ft_simulation(t_table *table);
void	*dinner(void *data);

// Monitor
void	*monitor(void *data);

#endif