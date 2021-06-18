/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:05:07 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/18 10:12:59 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	input_check(t_philo *ph)
{
	if (ph->number_of_philosophers > 200)
		return (1);
	if (ph->time_to_die < 60)
		return (1);
	if (ph->time_to_eat < 60)
		return (1);
	if (ph->time_to_sleep < 60)
		return (1);
	if (ph->is_must_eat && ph->number_of_times_each_philosopher_must_eat < 1)
		return (1);
	return (0);
}

void	ph_def_man(t_man *man)
{
	man->number_of_philosophers = 0;
	man->time_to_die = 0;
	man->time_to_eat = 0;
	man->time_to_sleep = 0;
	man->number_of_times_each_philosopher_must_eat = 0;
	man->is_must_eat = false;
	man->eat_cnt = 0;
	man->eat = NULL;
	man->left = NULL;
	man->right = NULL;
	man->died = NULL;
	man->fin = NULL;
	man->ate_cnt = NULL;
	man->lasteat = 0;
	man->id = 0;
}

int	ph_solo(t_philo *ph)
{
	long long	start;

	start = get_mtime();
	printf("%lld %d %s\n", start, 0, PFORK);
	printf("%lld %d %s\n", start + ph->time_to_die, 0, PDIED);
	return (0);
}

int	ph_init_man(t_philo *ph)
{
	t_man	man;
	int		i;

	ph->men = (t_man *)malloc(sizeof(t_man) * ph->number_of_philosophers);
	if (!ph->men)
		return (ft_error(EMALLOC));
	ph_def_man(&man);
	man.number_of_philosophers = ph->number_of_philosophers;
	man.time_to_die = ph->time_to_die;
	man.time_to_eat = ph->time_to_eat;
	man.time_to_sleep = ph->time_to_sleep;
	man.is_must_eat = ph->is_must_eat;
	man.number_of_times_each_philosopher_must_eat\
		= ph->number_of_times_each_philosopher_must_eat;
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		man.id = i + 1;
		ph->men[i] = man;
		ph->men[i].fin = &ph->fin;
	}
	return (0);
}

int	ph_init_arg(int argc, char *argv[], t_philo *ph)
{
	if (argc != 5 && argc != 6)
		return (ft_error(USAARG));
	ph->number_of_philosophers = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		ph->is_must_eat = true;
		ph->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
	if (input_check(ph))
		return (ft_error(USAVAL));
	if (ph->number_of_philosophers == 1)
		return (ph_solo(ph));
	return (0);
}
