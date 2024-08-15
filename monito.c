/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monito.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:26:00 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/15 14:00:48 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data_s->death_mutex);
	died = philo->data_s->dead;
	pthread_mutex_unlock(&philo->data_s->death_mutex);
	return (died);
}

void	one_philo(t_data *philo)
{
	pthread_create(&philo->philosophers[0].thread, NULL, routine_for_one_philo,
		&philo[0]);
	pthread_join(philo->philosophers[0].thread, NULL);
}

void	*routine_for_one_philo(void *ac)
{
	t_data	*philo;

	philo = (t_data *)ac;
	pthread_mutex_lock(&philo->philosophers->right_fork);
	pthread_mutex_lock(&philo->philosophers->mutex_printf);
	printf("%ld %d has taken a fork\n", (get_current_time()
			- philo->philosophers->time_start), philo->philosophers[0].id);
	pthread_mutex_unlock(&philo->philosophers->mutex_printf);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(&philo->philosophers->right_fork);
	pthread_mutex_lock(&philo->philosophers->mutex_printf);
	printf("%ld %d died\n", (get_current_time()
			- philo->philosophers->time_start), philo->philosophers[0].id);
	return(NULL);
}
