/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_watcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 09:48:58 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/15 13:15:14 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ph_watcher(void *p)
{
	int		i;
	t_philo	*ph;

	ph = p;
	while (!ph->fin)
	{
		i = -1;
		while (++i < ph->number_of_philosophers)
		{
			if (!ph->men[i].lasteat)
				continue ;
			if (ph->men[i].time_to_die <= get_mtime() - ph->men[i].lasteat)
			{
				ph_pout(&ph->men[i], PDIED);
				pthread_mutex_lock(&ph->died);
				ph->fin = true;
				pthread_mutex_unlock(&ph->died);
				return (NULL);
			}
		}
		usleep(200);
	}
	return (NULL);
}
