/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 07:27:19 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 11:31:38 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ph_kill_all(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		kill(ph->pid[i], SIGKILL);
	}
	if (ph->is_must_eat)
	{
		kill(ph->pid_watcher, SIGKILL);
	}
}

int	ph_launch(t_philo *ph)
{
	int	i;
	int	status;

	if (ph_launch_fork_philos(ph))
		return (1);
	if (ph->is_must_eat && ph_launch_eat_watcher(ph))
		return (1);
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status != SIGKILL)
		{
			ph_kill_all(ph);
		}
	}
	if (ph->is_must_eat)
	{
		waitpid(-1, &status, 0);
	}
	return (0);
}
