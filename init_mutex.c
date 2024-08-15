/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:45:09 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/14 21:35:41 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t ) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}
int	init_mutex(t_data *philo)
{
	if(pthread_mutex_init(&philo->death_mutex, NULL))
		return ((printf("Failed to initialize death_mutex\n")), 1);
	if(pthread_mutex_init(&philo->philosophers->mutex_eaten, NULL) != 0)
		return ((printf("Failed to initialize mutex_eaten\n")), 1);
	if(pthread_mutex_init(&philo->philosophers-> mutex_printf,NULL) != 0)
		return ((printf("Failed to initialize mutex_printf\n")), 1);
	return(0);
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 || philo->data_s->nbr_philo % 2 != 0)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void ft_put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}



