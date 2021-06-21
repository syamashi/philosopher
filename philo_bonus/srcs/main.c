/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:48:41 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/21 18:10:45 by user42           ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_philo	ph;

	ph = (t_philo){};
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
