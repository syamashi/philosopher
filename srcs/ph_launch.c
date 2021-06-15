/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 07:27:19 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/15 12:13:25 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
			ph_pout(man, PDIED);
			pthread_mutex_lock(man->died);
			*man->fin = true;
			pthread_mutex_unlock(man->died);
			return ;
		}
		if (time >= start + wait_time)
			return ;
		usleep(50);
	}
}

int	ph_work_fork(t_man *man)
{
	if (man->id % 2)
		pthread_mutex_lock(man->left);
	else
	{
		usleep(200);
		pthread_mutex_lock(man->right);
	}
	ph_pout(man, PFORK);
	if (man->id % 2)
	{
		usleep(200);
		pthread_mutex_lock(man->right);
	}
	else
		pthread_mutex_lock(man->left);
	ph_pout(man, PFORK);
	return (0);
}

int	ph_work_eat(t_man *man)
{
	++man->eat_cnt;
	if (man->is_must_eat &&
	man->eat_cnt == man->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(man->eat);
		++*man->ate_cnt;
		pthread_mutex_unlock(man->eat);
	}
	pthread_mutex_lock(man->died);
	if (*(man->ate_cnt) == man->number_of_philosophers)
		*man->fin = true;
	pthread_mutex_unlock(man->died);
	man->lasteat = get_mtime();
	ph_pout(man, PEAT);
	ph_wait(man, man->time_to_eat);
	pthread_mutex_unlock(man->right);
	pthread_mutex_unlock(man->left);
	return (0);
}

void	*ph_work(void *p)
{
	t_man *man = p;

	man->lasteat = get_mtime();
	while (!*man->fin)
	{
		ph_work_fork(man);
		ph_work_eat(man);
		ph_pout(man, PSLEEP);
		ph_wait(man, man->time_to_sleep);
		ph_pout(man, PTHINK);
	}
	return (NULL);
}

void	ph_launch(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		pthread_create(&ph->men[i].thread, NULL, &ph_work, (void *)&ph->men[i]);
	}
	pthread_create(&ph->watcher, NULL, &ph_watcher, (void *)ph);
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		pthread_join(ph->men[i].thread, NULL);
	}
	pthread_join(ph->watcher, NULL);
}
