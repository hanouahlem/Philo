/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:44:45 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/22 19:16:09 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		ft_eat(philo);
		ft_sleep_philosopher(philo);
		ft_think(philo);
		if (philo_is_dead(philo))
			break;
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	if (philo_is_dead(philo) == 1)
		return (0);
	ft_take_forks(philo);
	pthread_mutex_lock(&philo->last_meal);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal);
	print_status(philo, "is eating");
	ft_usleep(philo->data_s->time_to_eat);
	philo->meals_eaten++;
	ft_put_forks(philo);
	return (0);
}

void	ft_sleep_philosopher(t_philo *philo)
{
	ft_usleep(philo->data_s->time_to_sleep);
	print_status(philo, "is sleeping");
}

void	ft_think(t_philo *philo)
{
	if (philo_is_dead(philo))
	{
		print_status(philo, "died");
		return ; // Si le philosophe est mort, arrêtez son thread
	}
	ft_usleep(500);
	print_status(philo, "is thinking");
}