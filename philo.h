/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:41:13 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/15 13:53:04 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	long				last_meal_time;
	long				time_start;
	int					meals_eaten;
	pthread_mutex_t		mutex_printf;
	pthread_mutex_t		mutex_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		right_fork;
	t_data				*data_s;
}						t_philo;

typedef struct s_data
{
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					dead;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death_mutex;
	t_philo				*philosophers;
}						t_data;

int						ft_not_digit(int ac, char **av);
void					make_init(int ac, char **av, t_data *data);
int						check_max_min(char **av);
int						ft_check_error(int ac, char **av);
long					ft_atoi(char *str);
int						ft_isdigit(int c);

void					*philosopher_life(void *arg);
void					ft_take_forks(t_philo *philo);
void					ft_put_forks(t_philo *philo);
long					get_current_time(void);

void					init_forks(t_data *data);
void					init_philos(t_data *data);
int						init_mutex(t_data *philo);
void					init_threads(t_data *data);

void					one_philo(t_data *philo);
void					*routine_for_one_philo(void *ac);
int						ft_dead(t_philo *philo);

void					ft_think(t_philo *philo);
int						ft_eat(t_philo *philo);
void					ft_sleep_philosopher(t_philo *philo);
void					print_status(t_philo *philo, const char *status);
void					free_all(t_data *data);
long					ft_usleep(long data);

#endif