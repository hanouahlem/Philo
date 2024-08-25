/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:41:07 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/21 20:31:03 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%ld %d has taken a fork\n", (get_current_time()
			- philo->philosophers->time_start), philo->philosophers[0].id);
	pthread_mutex_unlock(&philo->mutex_printf);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(&philo->philosophers->right_fork);
	pthread_mutex_lock(&philo->mutex_printf);
	printf("%ld %d died\n", (get_current_time()
			- philo->philosophers->time_start), philo->philosophers[0].id);
	return (NULL);
}

int	main(int ac, char **av)
{
	static t_data	philo = {0};
	int				i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (printf("numbers of arguments is wrong\n"), 0);
	ft_check_error(ac, av);
	make_init(ac, av, &philo);
	init_forks(&philo);
	init_philos(&philo);
	init_mutex(&philo, philo.philosophers);
	if (philo.nbr_philo == 1)
	{
		one_philo(&philo);
		free_all(&philo);
		return (0);
	}
	printf("nbr philo : %d\n time die : %d\n time eat : %d\n time sleep : %d\n must eat : %d\n", philo.nbr_philo, philo.time_to_die,
		philo.time_to_eat, philo.time_to_sleep, philo.must_eat);
	init_threads(&philo, philo.philosophers);
	while (i < philo.nbr_philo)
	{
		pthread_join(philo.philosophers[i].thread, NULL);
		i++;
	}
	free_all(&philo);
	return (0);
}
