/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:15:15 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/06 15:34:46 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	if (philo->nbr_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo);
		ft_usleep(philo->time_to_die + 1);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	lock_forks(philo);
	pthread_mutex_lock(philo->eat_lock);
	philo->eating = 1;
	philo->meals_counter++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eat_lock);
	print_message("is eating", philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->eat_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->eat_lock);
	unlock_forks(philo);
}

static void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	long	think_time;

	print_message("is thinking", philo);
	think_time = ((long)philo->time_to_die - philo->time_to_eat
			- philo->time_to_sleep) / 2;
	if (think_time > 0)
		ft_usleep(think_time);
}

static int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(philo->dead_lock);
	dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (dead);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	while (1)
	{
		if (is_dead(philo))
			return (pointer);
		eating(philo);
		if (is_dead(philo))
			return (pointer);
		sleeping(philo);
		thinking(philo);
	}
	return (pointer);
}
