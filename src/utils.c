/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:23:11 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/11 10:09:03 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(const char *message)
{
	printf("Error : %s\n", message);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->start;
	pthread_mutex_lock(philo->dead_lock);
	pthread_mutex_lock(philo->write_lock);
	if (!*philo->dead)
		printf("%zu %d %s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(philo->dead_lock);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(500);
	return (0);
}

void	destroy_all(t_programm *prog)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->eat_lock);
	pthread_mutex_destroy(&prog->write_lock);
	while (i < prog->nbr_philos)
	{
		pthread_mutex_destroy(&prog->fork[i]);
		i++;
	}
	free(prog->fork);
	free(prog->philo);
}
