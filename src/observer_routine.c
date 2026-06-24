/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:23:00 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/05 12:05:58 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead_check(t_philo	*philo)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_time() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

static int	philo_dead_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nbr_philos)
	{
		if (is_dead_check(&philo[i]) != 0)
		{
			print_message("died", &philo[i]);
			pthread_mutex_lock(philo[i].dead_lock);
			*philo[i].dead = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philos_are_full(t_philo *philo)
{
	int	finished_eating;	
	int	i;

	i = 0;
	finished_eating = 0;
	if (philo->nbr_of_meals == -1)
		return (0);
	while (i < philo->nbr_philos)
	{
		pthread_mutex_lock(philo[i].eat_lock);
		if (philo[i].meals_counter >= philo->nbr_of_meals)
			finished_eating++;
		pthread_mutex_unlock(philo[i].eat_lock);
		i++;
	}
	if (finished_eating == philo->nbr_philos)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

void	*observer_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (philo_dead_check(philo) == 1 || philos_are_full(philo) == 1)
			break ;
		usleep(1000);
	}
	return (pointer);
}
