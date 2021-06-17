/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_fork_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:06:07 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/15 13:27:02 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ph_init_eat(t_philo *ph)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&ph->eat, NULL))
		return (ft_error(EMUTEX));
	ph->ate_cnt = 0;
	while (++i < ph->number_of_philosophers)
	{
		ph->men[i].ate_cnt = &ph->ate_cnt;
		ph->men[i].eat = &ph->eat;
	}
	return (0);
}

int	ph_init_fork(t_philo *ph)
{
	int	i;
	int	people;

	people = ph->number_of_philosophers;
	if (pthread_mutex_init(&ph->died, NULL))
		return (ft_error(EMUTEX));
	ph->fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * ph->number_of_philosophers);
	if (!ph->fork)
		return (ft_error(EMALLOC));
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		if (pthread_mutex_init(&ph->fork[i], NULL))
			return (ft_error(EMUTEX));
	}
	i = -1;
	while (++i < people)
	{
		ph->men[i].left = &ph->fork[i];
		ph->men[i].right = &ph->fork[(i - 1 + people) % people];
		ph->men[i].died = &ph->died;
	}
	return (0);
}
