/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:44:45 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/15 14:25:07 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_life(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(500);
	while (1)
	{
		ft_eat(philo);
		ft_sleep_philosopher(philo);
		ft_think(philo);
		i++;
	}
	return (NULL);
}

void	ft_think(t_philo *philo)
{
	ft_usleep(philo->data_s->time_to_sleep);
	print_status(philo, "thinking");
}

int	ft_eat(t_philo *philo)
{
	if(ft_dead(philo) == 1)
		return (0);
	ft_take_forks(philo);
	philo->last_meal_time = get_current_time();
	print_status(philo, "eating");
	ft_usleep(philo->data_s->time_to_eat);
	philo->meals_eaten++;
	ft_put_forks(philo);
	return (0);
}

void	ft_sleep_philosopher(t_philo *philo)
{
	ft_usleep(philo->data_s->time_to_sleep);
	print_status(philo, "sleeping");
}
