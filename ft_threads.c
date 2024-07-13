/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: murathanelcuman <murathanelcuman@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:47:15 by murathanelc       #+#    #+#             */
/*   Updated: 2024/07/13 13:49:20 by murathanelc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create(pthread_t th, void *(*foo)(void *), void *data)
{
	if (pthread_create(&th, NULL, foo, data) != 0)
		return (ft_error("Failed at creating thread"));
	return (0);
}

int	join(pthread_t th)
{
	if (pthread_join(th, NULL) != 0)
		return (ft_error("Failed at joining thread"));
	return (0);
}
