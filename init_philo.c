/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:22:16 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/23 18:10:34 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_make_philo(void *id)
{
    int *num = id;
	t_philo *philo;
	
    while (1) { // Boucle infinie pour le philosophe
        printf("Philosophe %d pense\n", *num);
        pthread_mutex_lock(&forks[*num]);
        pthread_mutex_lock(&forks[(*num + 1) % philo->nbr_philo]);

        printf("Philosophe %d mange\n", *num);

        pthread_mutex_unlock(&forks[*num]);
        pthread_mutex_unlock(&forks[(*num + 1) % philo]);

        printf("Philosophe %d dort\n", *num);
        sleep(1); // Simule le temps de sommeil
    }
}

int	create_philo(t_philo *philo)
{
	int	i;
	int	num;
	int *threads

	i = 0;
	while (i < philo->nbr_philo)
	{ // Boucle while pour créer les threads
		num = i + 1;
		pthread_create(&threads[i], NULL, make_philo, &num);
		i++;
	}
}
