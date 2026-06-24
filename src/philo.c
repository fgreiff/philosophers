/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:15:13 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/11 10:09:41 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_programm	prog;
	int			rc;

	if (argc < 5 || argc > 6)
	{
		print_error("Usage: ./philo <nbr> <die> <eat> <sleep> [meals]");
		return (1);
	}
	if (parse_input(&prog, argv) == -1)
		return (1);
	init_philo(&prog);
	rc = thread_init(&prog);
	destroy_all(&prog);
	return (rc);
}
