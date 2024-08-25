/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monito.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:26:00 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/22 19:39:20 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data_s->death_mutex);
	died = philo->data_s->dead;
	pthread_mutex_unlock(&philo->data_s->death_mutex);
	return (died);
	// if (died == 0)
	// 	return (1);
	// return (0);
}

int	check_if_death(t_philo *philo)
{
	int	i;

	i = 0;
	printf("hello\n");
	while (i < philo->data_s->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_eaten);
		if (philo[0].data_s->time_to_die <= get_current_time()
			- philo[i].last_meal_time)
		{
			pthread_mutex_lock(&philo->data_s->death_mutex);
			philo->data_s->dead = 1;
			pthread_mutex_unlock(&philo->data_s->death_mutex);
			pthread_mutex_lock(&philo[0].data_s->mutex_printf);
			print_status(philo, " is died");
			pthread_mutex_unlock(&philo[0].data_s->mutex_printf);
			pthread_mutex_unlock(&philo[i].mutex_eaten);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].mutex_eaten);
		i++;
	}
	return (0);
}


int	process_monito(t_philo *philo)
{
	int i;

	while (1)
	{
		if (philo->data_s->must_eat != 1)
		{
			i = 0;
			while (i < philo->data_s->nbr_philo)
			{
				pthread_mutex_lock(&philo->data_s->eaten_mtx);
				if (philo->data_s->philo_eaten == philo->data_s->nbr_philo)
					return (pthread_mutex_unlock(&philo->data_s->eaten_mtx), 1);
				pthread_mutex_unlock(&philo->data_s->eaten_mtx);
				i++;
			}
			return (1);
		}
		if (check_if_death(philo))
			return (1);
	}
}