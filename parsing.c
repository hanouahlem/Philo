/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbey <ahbey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:19:51 by ahbey             #+#    #+#             */
/*   Updated: 2024/08/19 16:59:30 by ahbey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		nb = ft_atoi(av[i]);
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
