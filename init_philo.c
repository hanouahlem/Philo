/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:35 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/31 19:22:00 by ahbey            ###   ########.fr       */
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
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forck[i];
		data->philosophers[i].right_fork = data->forck[(i + 1)
			* data->nbr_philo];	
		data->philosophers[i].last_meal_time = get_current_time();
		data->philosophers[i].meals_eaten = 0;
		i++;
	}
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_sec / 1000));
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_create(&data->philosophers[i].thread, NULL, philos_life,
			&data->philosophers);
		i++;
	}
}

void	*philos_life(void *arg)
{
		t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (1)
	{
		printf("hello dans init life\n");
	
		// think(philosopher);
		// take_forks(philosopher);
		// eat(philosopher);
		// put_forks(philosopher);
		// sleep_philosopher(philosopher);
		printf("hello dans init life apres thinkn\n");
	}
	return (NULL);
}
