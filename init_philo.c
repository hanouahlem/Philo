/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/14 14:35:32 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philo) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		data->philosophers[i].data_s = data;
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = data->forks[(i + 1)
			% data->nbr_philo];
		data->philosophers[i].last_meal_time = get_current_time();
		data->philosophers[i].time_start = get_current_time();
		// printf("%ld\n", get_current_time() - data->philosophers[i].time_start);
		data->philosophers[i].meals_eaten = 0;
		i++;
	}
}

void	init_threads(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&table->philosophers[i].thread, NULL, philosopher_life,
			&table->philosophers[i]);
		i++;
	}
	
}
// printf("id  = %d addr l = %p addrr R = %p\n ", (i + 1) % data->nbr_philo,
// data->philosophers[i].id, data->philosophers[i].left_fork);
// void ft_usleep()

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_sec / 1000));
}


void	print_status(t_philo *philo, const char *status)
{
	// printf("time-start = %ld\nGet_time %ld\n", philo->time_start,
	// 	get_current_time());
	printf("%ld philo %d is %s\n", (get_current_time() - philo->time_start),
		philo->id, status);
}

long	ft_usleep(long data)
{
	long time;

	time = get_current_time();
	while ((get_current_time() - time) < data)
		usleep(1000);
	return (0);
}