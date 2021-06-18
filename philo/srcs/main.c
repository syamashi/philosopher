/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:48:41 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/18 10:13:16 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_mutex_destroy(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		pthread_mutex_destroy(&ph->fork[i]);
	}
	pthread_mutex_destroy(&ph->died);
	pthread_mutex_destroy(&ph->eat);
}

int	all_free(t_philo *ph)
{
	free(ph->men);
	free(ph->fork);
	return (0);
}

void	ph_def(t_philo *ph)
{
	ph->fin = false;
	ph->fork = NULL;
	ph->men = NULL;
	ph->number_of_philosophers = 0;
	ph->time_to_die = 0;
	ph->time_to_eat = 0;
	ph->time_to_sleep = 0;
	ph->number_of_times_each_philosopher_must_eat = 0;
	ph->is_must_eat = false;
	ph->ate_cnt = 0;
}

int	main(int argc, char *argv[])
{
	t_philo	ph;

	ph_def(&ph);
	if (ph_init_arg(argc, argv, &ph))
		return (0);
	if (ph_init_man(&ph))
		return (all_free(&ph));
	if (ph_init_fork(&ph))
		return (all_free(&ph));
	if (ph_init_eat(&ph))
		return (all_free(&ph));
	ph_launch(&ph);
	ph_mutex_destroy(&ph);
	all_free(&ph);
	return (0);
}
