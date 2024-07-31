/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:41:07 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/31 19:31:16 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int ac, char **av)
{
	static t_data	philo = {0};
	int i;
	
	i = 0;
	if (ac != 5 && ac != 6)
		return (printf("numbers of arguments is wrong\n"), 0);
	ft_check_error(ac, av);
	make_init(ac, av, &philo);
	init_forks(&philo);
	init_philos(&philo);
	init_threads(&philo);
	printf("nbr philo : %d\n time die : %d\n time eat : %d\n time sleep : %d\n must eat : %d\n", philo.nbr_philo, philo.time_to_die,
		philo.time_to_eat, philo.time_to_sleep, philo.must_eat);
	return (0);
}
