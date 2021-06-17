/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:48:41 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 12:04:45 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	all_free(t_philo *ph)
{
	free(ph->men);
	return (1);
}

void	ph_sem_close(t_philo *ph)
{
	int	i;

	sem_close(ph->pout);
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		sem_close(ph->men[i].fork);
		sem_close(ph->men[i].eat);
	}
}

void	ph_def(t_philo *ph)
{
	int	i;

	ph->is_must_eat = 0;
	i = -1;
	while (++i < 210)
	{
		ph->eat_cnt[i] = 0;
	}
	ph->number_of_philosophers = 0;
	ph->number_of_times_each_philosopher_must_eat = 0;
	ph->is_must_eat = 0;
}

int	main(int argc, char *argv[])
{
	t_philo	ph;

	ph_def(&ph);
	if (ph_init_arg(argc, argv, &ph))
		return (all_free(&ph));
	if (ph_init_sem(&ph))
		return (all_free(&ph));
	if (ph_launch(&ph))
	{
		ph_sem_close(&ph);
		return (all_free(&ph));
	}
	ph_sem_close(&ph);
	all_free(&ph);
	return (0);
}
