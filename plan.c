#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// Définition des structures
typedef struct Philosopher_s
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	 struct table		*table;
}					Philosopher;

typedef struct table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*forks;
	Philosopher		*philosophers;
}					Table_t;

// Prototypes de fonctions
void				init_philosophers(Table_t *table);
void				init_forks(Table_t *table);
void				init_threads(Table_t *table);
void				*philosopher_life(void *arg);
void				think(Philosopher *philosopher);
void				eat(Philosopher *philosopher);
void				sleep_philosopher(Philosopher *philosopher);
void				take_forks(Philosopher *philosopher);
void				put_forks(Philosopher *philosopher);
void				*monitor(void *arg);
long				get_current_time(void);
void				print_status(Philosopher *philosopher, const char *status);
void				cleanup(Table_t *table);

int	main(int argc, char **argv)
{
	Table_t	table;

	if (argc < 5 || argc > 6)
	{
		printf("number of argv is wrong\n");
		return (1);
	}
	// Initialisation des variables à partir des arguments
	table.number_of_philosophers = atoi(argv[1]);
	table.time_to_die = atoi(argv[2]);
	table.time_to_eat = atoi(argv[3]);
	table.time_to_sleep = atoi(argv[4]);
	table.number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) :
		-1;
	// Initialisation des philosophes et des fourchettes
	init_forks(&table);
	init_philosophers(&table);
	init_threads(&table);
	// Attendre que tous les threads se terminent
	for (int i = 0; i < table.number_of_philosophers; i++)
	{
		pthread_join(table.philosophers[i].thread, NULL);
	}
	// Nettoyage des ressources
	cleanup(&table);
	return (0);
}

// Implémentations des fonctions
void	init_philosophers(Table_t *table)
{
	int	i;

	table->philosophers = malloc(sizeof(Philosopher)
			* table->number_of_philosophers);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = &table->forks[i];
		table->philosophers[i].right_fork = &table->forks[(i + 1)
			% table->number_of_philosophers];
		table->philosophers[i].last_meal_time = get_current_time();
		table->philosophers[i].meals_eaten = 0;
		i++;
	}
}

void	init_forks(Table_t *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosophers);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	init_threads(Table_t *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_create(&table->philosophers[i].thread, NULL, philosopher_life,
			&table->philosophers[i]);
		i++;
	}
}

void	*philosopher_life(void *arg)
{
	Philosopher	*philosopher;

	philosopher = (Philosopher *)arg;
	while (1)
	{
		think(philosopher);
		take_forks(philosopher);
		eat(philosopher);
		put_forks(philosopher);
		sleep_philosopher(philosopher);
	}
	return (NULL);
}

void	think(Philosopher *philosopher)
{
	print_status(philosopher, "thinking");
	usleep(philosopher->table->time_to_sleep * 1000);
}

void	eat(Philosopher *philosopher)
{
	print_status(philosopher, "eating");
	usleep(philosopher->table->time_to_eat * 1000);
	philosopher->last_meal_time = get_current_time();
	philosopher->meals_eaten++;
}

void	sleep_philosopher(Philosopher *philosopher)
{
	print_status(philosopher, "sleeping");
	usleep(philosopher->table->time_to_sleep * 1000);
}

void	take_forks(Philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(philosopher->right_fork);
}

void	put_forks(Philosopher *philosopher)
{
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	*monitor(void *arg)
{
	Table_t	*table;
	int		i;

	table = (Table_t *)arg;
	while (1)
	{
		i = 0;
		while (i < table->number_of_philosophers)
		{
			if (get_current_time()
				- table->philosophers[i].last_meal_time > table->time_to_die)
			{
				print_status(&table->philosophers[i], "died");
				exit(0);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	print_status(Philosopher *philosopher, const char *status)
{
	printf("Philosopher %d is %s\n", philosopher->id, status);
}

void	cleanup(Table_t *table)
{
	int i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philosophers);
}