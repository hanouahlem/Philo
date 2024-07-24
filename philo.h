/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:41:13 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/24 17:36:41 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data;

typedef struct s_philo
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	t_data *data_s_ta_mere_en_splip_a_la_rochelle;
}		t_philo;

// typedef struct s_data
// {
// 	t_philo philo_s;
	
	
// }	t_data;

int		ft_not_digit(int ac, char **av);
void	make_init(int ac, char **av, t_philo *philo);
int		check_max_min(char **av);
int		ft_check_error(int ac, char **av);
long	ft_atoii(char *str);

#endif