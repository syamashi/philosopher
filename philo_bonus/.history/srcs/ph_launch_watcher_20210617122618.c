/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_launch_watcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:49:33 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 12:26:18 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*ph_watcher(void *p)
{
	int		i;
	t_man	*man;

	man = p;
	while (1)
	{
		i = -1;
		while (++i < man->number_of_philosophers)
		{
			if (!man->lasteat)
				continue ;
			if (man->time_to_die <= get_mtime() - man->lasteat)
			{
				ph_pout_died(man, PDIED);
				exit(0);
			}
		}
		usleep(200);
	}
	return (NULL);
}

void	ph_eat_watcher(t_philo *ph)
{
	int		i;
	int		full_cnt;

	full_cnt = 0;
	i = -1;
	while (full_cnt < ph->number_of_philosophers)
	{
		i = -1;
		while (++i < ph->number_of_philosophers)
		{
			sem_wait(ph->men[i].eat);
			++ph->eat_cnt[i];
			if (ph->eat_cnt[i] ==\
				ph->number_of_times_each_philosopher_must_eat)
				++full_cnt;
		}
		usleep(200);
	}
	exit(0);
}

int	ph_launch_eat_watcher(t_philo *ph)
{
	ph->pid_watcher = fork();
	if (ph->pid_watcher < 0)
		return (ft_error(EFORK));
	if (ph->pid_watcher == 0)
	{
		ph_eat_watcher(ph);
	}
	return (0);
}
