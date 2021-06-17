/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_launch_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:47:08 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 12:26:34 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ph_wait(t_man *man, int wait_time)
{
	long long	start;
	long long	time;

	start = get_mtime();
	while (1)
	{
		time = get_mtime();
		if (man->time_to_die <= time - man->lasteat)
		{
			ph_pout_died(man, PDIED);
			sem_wait(man->pout);
			exit(0);
		}
		if (time >= start + wait_time)
			return ;
		usleep(50);
	}
}

int	ph_work_fork(t_man *man)
{
	if (man->id % 2)
		usleep(500);
	sem_wait(man->fork);
	ph_pout(man, PFORK);
	sem_wait(man->fork);
	ph_pout(man, PFORK);
	return (0);
}

int	ph_work_eat(t_man *man)
{
	ph_pout(man, PEAT);
	sem_post(man->eat);
	man->lasteat = get_mtime();
	ph_wait(man, man->time_to_eat);
	sem_post(man->fork);
	sem_post(man->fork);
	return (0);
}

void	ph_work(t_man *man)
{
	man->lasteat = get_mtime();
	while (1)
	{
		ph_work_fork(man);
		ph_work_eat(man);
		ph_pout(man, PSLEEP);
		ph_wait(man, man->time_to_sleep);
		ph_pout(man, PTHINK);
	}
}

int	ph_launch_fork_philos(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		ph->pid[i] = fork();
		if (ph->pid[i] < 0)
			return (ft_error(EFORK));
		if (ph->pid[i] == 0)
		{
			pthread_create(&ph->men[i].thread, NULL, &ph_watcher, \
				(void *)&ph->men[i]);
			ph_work(&ph->men[i]);
			pthread_join(ph->men[i].thread, NULL);
			exit(0);
		}
	}
	return (0);
}
