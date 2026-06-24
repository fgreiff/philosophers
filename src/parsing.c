/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:16:26 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/11 10:23:46 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*validate_input(char *str)
{
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		print_error("Negative numbers are invalid!");
		return (NULL);
	}
	if (!is_num(&str[i]))
	{
		print_error("Input must be numerical!");
		return (NULL);
	}
	return (&str[i]);
}

static long	ft_atol(char *str, int *err)
{
	long	nbr;
	char	*number;
	int		i;

	number = validate_input(str);
	if (!number)
	{
		*err = 1;
		return (0);
	}
	i = 0;
	nbr = 0;
	while (number[i] && number[i] >= 48 && number[i] <= 57)
	{
		nbr = (nbr * 10) + (number[i] - 48);
		i++;
		if (nbr > INT_MAX)
		{
			print_error("Input bigger than INT_MAX!");
			*err = 1;
			return (0);
		}
	}
	return (nbr);
}

static void	init_mutexes(t_programm *prog)
{
	int	i;

	i = 0;
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->eat_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	while (i < prog->nbr_philos)
	{
		pthread_mutex_init(&prog->fork[i], NULL);
		i++;
	}
}

int	parse_input(t_programm *prog, char **argv)
{
	int	err;

	err = 0;
	prog->nbr_philos = ft_atol(argv[1], &err);
	prog->time_to_die = ft_atol(argv[2], &err);
	prog->time_to_eat = ft_atol(argv[3], &err);
	prog->time_to_sleep = ft_atol(argv[4], &err);
	if (prog->nbr_philos == 0)
		return (-1);
	if (argv[5])
		prog->max_meals = ft_atol(argv[5], &err);
	else
		prog->max_meals = -1;
	if (err)
		return (-1);
	prog->is_dead = 0;
	prog->fork = malloc(sizeof(t_mtx) * prog->nbr_philos);
	prog->philo = malloc(sizeof(t_philo) * prog->nbr_philos);
	init_mutexes(prog);
	return (0);
}
