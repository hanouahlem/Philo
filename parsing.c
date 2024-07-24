/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:19:51 by ahbey             #+#    #+#             */
/*   Updated: 2024/07/16 21:42:19 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void make_init(int ac, char **av, t_philo *philo)
{
		philo->nbr_philo = ft_atoii(av[1]);
		philo-> time_to_die = ft_atoii(av[2]);
		philo->time_to_eat = ft_atoii(av[3]);
		philo->time_to_sleep = ft_atoii(av[4]);
		philo->must_eat = -1;
	if (ac == 6)
		philo->must_eat = ft_atoii(av[5]);
}

int	ft_not_digit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_max_min(char **av)
{
	int		i;
	long	nb;

	i = 1;
	while (av[i])
	{
		nb = ft_atoii(av[i]);
		if (nb > INT_MAX || nb < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_error(int ac, char **av)
{
	if (check_max_min(av))
		return (write(2, "Error int\n", 10));
	if (ft_not_digit(ac, av))
		return (write(2, "Error not digit\n", 16));
	return (0);
}
