#include "philo.h"

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_mutex(t_data *philo, t_philo *data)
{
	if (pthread_mutex_init(&philo->death_mutex, NULL))
		return ((printf("Failed to initialize death_mutex\n")), 1);
	if (pthread_mutex_init(&data->mutex_eaten, NULL) != 0)
		return ((printf("Failed to initialize mutex_eaten\n")), 1);
	if (pthread_mutex_init(&philo->mutex_printf, NULL) != 0)
		return ((printf("Failed to initialize mutex_printf\n")), 1);
	if (pthread_mutex_init(&philo->eaten_mtx, NULL) != 0)
		return ((printf("Failed to initialize eaten_mtx\n")), 1);
	if (pthread_mutex_init(&data->last_meal, NULL) != 0)
		return ((printf("Failed to initialize last_meal\n")), 1);
	return (0);
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
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

void	ft_put_forks(t_philo *philo)
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

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philo) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		data->philosophers[i].data_s = data;
		data->philosophers[i].id = i + 1;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = data->forks[(i + 1)
			% data->nbr_philo];
		data->philosophers[i].last_meal_time = get_current_time();
		data->philosophers[i].time_start = get_current_time();
		data->philosophers[i].meals_eaten = 0;
		i++;
	}
}

void	init_threads(t_data *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&table->philosophers[i].thread, NULL, philosopher_life,
			&table->philosophers[i]);
		i++;
	}
	process_monito(philo);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->data_s->mutex_printf);
	printf("%ld %d %s\n", (get_current_time() - philo->time_start), philo->id,
		status);
	pthread_mutex_unlock(&philo->data_s->mutex_printf);
}

long	ft_usleep(long data)
{
	long time;

	time = get_current_time();
	while ((get_current_time() - time) < data)
		usleep(100);
	return (0);
}

int	philo_is_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data_s->death_mutex);
	died = philo->data_s->dead;
	pthread_mutex_unlock(&philo->data_s->death_mutex);
	return (died);
}

int	check_if_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data_s->nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_eaten);
		if (philo[0].data_s->time_to_die <= get_current_time()
			- philo[i].last_meal_time)
		{
			pthread_mutex_lock(&philo->data_s->death_mutex);
			philo->data_s->dead = 1;
			pthread_mutex_unlock(&philo->data_s->death_mutex);
			pthread_mutex_lock(&philo[0].data_s->mutex_printf);
			print_status(philo, " is died");
			
			pthread_mutex_unlock(&philo[0].data_s->mutex_printf);
			pthread_mutex_unlock(&philo[i].mutex_eaten);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].mutex_eaten);
		i++;
	}
	return (0);
}

int	process_monito(t_philo *philo)
{
	int i;
	
	while (philo_is_dead(philo) == 0)
	{
		if (philo->data_s->must_eat != 1)
		{
			i = 0;
			while (i < philo->data_s->nbr_philo)
			{
				pthread_mutex_lock(&philo->data_s->eaten_mtx);
				if (philo->data_s->philo_eaten == philo->data_s->nbr_philo)
					return (pthread_mutex_unlock(&philo->data_s->eaten_mtx), 1);
				pthread_mutex_unlock(&philo->data_s->eaten_mtx);
				i++;
			}
			return(1);
		}
		if (check_if_death(philo))
			return (1);
	}
}

void	make_init(int ac, char **av, t_data *data)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	data->philo_eaten = 0;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
}

int	ft_check_error(int ac, char **av)
{
	if (check_max_min(av))
		return (write(2, "Error int\n", 10));
	if (ft_not_digit(ac, av))
		return (write(2, "Error not digit\n", 16));
	return (0);
}
void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		ft_eat(philo);
		ft_sleep_philosopher(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	if (philo_is_dead(philo) == 1)
		return (0);
	ft_take_forks(philo);
	pthread_mutex_lock(&philo->last_meal);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal);
	print_status(philo, "is eating");
	ft_usleep(philo->data_s->time_to_eat);
	philo->meals_eaten++;
	ft_put_forks(philo);
	return (0);
}

void	ft_sleep_philosopher(t_philo *philo)
{
	ft_usleep(philo->data_s->time_to_sleep);
	print_status(philo, "is sleeping");
}

void	ft_think(t_philo *philo)
{
	ft_usleep(500);
	print_status(philo, "is thinking");
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