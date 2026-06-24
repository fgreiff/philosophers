/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:57:30 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/11 10:04:49 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_philo_fields(t_programm *prog, int i, size_t start)
{
	prog->philo[i].philo_id = i + 1;
	prog->philo[i].meals_counter = 0;
	prog->philo[i].eating = 0;
	prog->philo[i].start = start;
	prog->philo[i].last_meal = start;
	prog->philo[i].time_to_die = prog->time_to_die;
	prog->philo[i].time_to_eat = prog->time_to_eat;
	prog->philo[i].time_to_sleep = prog->time_to_sleep;
	prog->philo[i].nbr_philos = prog->nbr_philos;
	prog->philo[i].nbr_of_meals = prog->max_meals;
	prog->philo[i].dead = &prog->is_dead;
	prog->philo[i].dead_lock = &prog->dead_lock;
	prog->philo[i].eat_lock = &prog->eat_lock;
	prog->philo[i].write_lock = &prog->write_lock;
	prog->philo[i].l_fork = &prog->fork[i];
	if (i == 0)
		prog->philo[i].r_fork = &prog->fork[prog->nbr_philos - 1];
	else
		prog->philo[i].r_fork = &prog->fork[i - 1];
}

void	init_philo(t_programm *prog)
{
	int		i;
	size_t	start;

	i = 0;
	start = get_time();
	while (i < prog->nbr_philos)
	{
		assign_philo_fields(prog, i, start);
		i++;
	}
}

static int	shutdown_threads(t_programm *prog, int created)
{
	int	i;

	pthread_mutex_lock(&prog->dead_lock);
	prog->is_dead = 1;
	pthread_mutex_unlock(&prog->dead_lock);
	i = 0;
	while (i < created)
	{
		pthread_join(prog->philo[i].thread, NULL);
		i++;
	}
	print_error("Thread creation failed!");
	return (1);
}

int	thread_init(t_programm *prog)
{
	int			i;
	pthread_t	observer;

	i = 0;
	while (i < prog->nbr_philos)
	{
		if (pthread_create(&prog->philo[i].thread, NULL,
				&philo_routine, &prog->philo[i]) != 0)
			return (shutdown_threads(prog, i));
		i++;
	}
	if (pthread_create(&observer, NULL, &observer_routine, prog->philo) != 0)
		return (shutdown_threads(prog, prog->nbr_philos));
	pthread_join(observer, NULL);
	i = 0;
	while (i < prog->nbr_philos)
	{
		pthread_join(prog->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
