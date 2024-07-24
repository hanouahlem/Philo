/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:41:07 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/19 19:58:36 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	static t_philo	philo = {0};

	if (ac != 5 && ac != 6)
		return (ft_printf("numbers of arguments is wrong\n"), 0);
	ft_check_error(ac, av);
	make_init(ac, av, &philo);
	printf("nbr philo : %d\n time die : %d\n time eat : %d\n time sleep : %d\n must eat : %d\n", philo.nbr_philo, philo.time_to_die,
		philo.time_to_eat, philo.time_to_sleep, philo.must_eat);
	 int i = 0;
    while (i < philo.nbr_philo) 
	{ // Boucle while pour créer les threads
        int num = i + 1;
        pthread_create();
        i++;
    }
	return (0);
}
