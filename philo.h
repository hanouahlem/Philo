/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:41:13 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/31 19:33:35 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_data	s_data;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		right_fork;
	long				last_meal_time;
	int					meals_eaten;
	pthread_t			thread;
	s_data				*data_s;
}						t_philo;

typedef struct s_data
{
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;

	pthread_mutex_t		*forck;
	t_philo				*philosophers;
}						t_data;

int						ft_not_digit(int ac, char **av);
void					make_init(int ac, char **av, t_data *data);
int						check_max_min(char **av);
int						ft_check_error(int ac, char **av);
long					ft_atoii(char *str);

void					init_forks(t_data *data);
void					init_philos(t_data *data);
void					init_threads(t_data *data);
void					*philos_life(void *arg);
void					take_forks(t_philo *philo);
void					put_forks(t_philo *philo);
long					get_current_time(void);

#endif