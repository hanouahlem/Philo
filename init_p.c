/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:19:47 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/29 18:19:47 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"
void *make_philo(void *id)
{
    int *num = id;
	t_data *philo;
	
    while (1) { // Boucle infinie pour le philosophe
        printf("Philosophe %d pense\n", *num);
        // pthread_mutex_lock(&forks[*num]);
        // pthread_mutex_lock(&forks[(*num + 1) % philo->nbr_philo]);

        printf("Philosophe %d mange\n", *num);

        // pthread_mutex_unlock();
        // pthread_mutex_unlock();

        printf("Philosophe %d dort\n", *num);
        sleep(1); // Simule le temps de sommeil
    }
}

int	create_philo(t_data *philo)
{
	int	i;
	int	num;
	int *threads;

	i = 0;
	while (i < philo->nbr_philo)
	{ // Boucle while pour créer les threads
		
		pthread_create(&threads[i], NULL, make_philo, NULL);
		i++;
	}
}
// philo eat
// philo sleep
// philo think 
