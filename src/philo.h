/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:19:49 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/11 10:09:28 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo 
{
	pthread_t	thread;
	size_t		last_meal;
	size_t		start;
	size_t		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_philos;	
	int			meals_counter;
	int			philo_id;
	int			eating;
	int			*dead;
	int			nbr_of_meals;
	t_mtx		*dead_lock;
	t_mtx		*write_lock;
	t_mtx		*eat_lock;
	t_mtx		*l_fork;
	t_mtx		*r_fork;
}	t_philo;

typedef struct s_programm
{
	long	nbr_philos;	
	t_philo	*philo;
	t_mtx	*fork;
	size_t	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meals;
	int		is_dead;
	t_mtx	dead_lock;
	t_mtx	write_lock;
	t_mtx	eat_lock;
}	t_programm;

int		main(int argc, char **argv);

//parsing
int		parse_input(t_programm *prog, char **argv);

//utils
int		is_num(char *str);
int		ft_isspace(char c);
size_t	get_time(void);
void	print_message(char *str, t_philo *philo);
int		ft_usleep(size_t milliseconds);

//init
void	init_philo(t_programm *prog);
int		thread_init(t_programm *prog);

//routines
void	*philo_routine(void *pointer);
void	*observer_routine(void *pointer);
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);

void	print_error(const char *message);
void	destroy_all(t_programm *prog);
#endif