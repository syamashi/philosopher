/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:05:07 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/15 12:22:38 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	input_check(t_man *man, int num)
{
	if (num > 200)
		return (1);
	if (man->time_to_die < 60)
		return (1);
	if (man->time_to_eat < 60)
		return (1);
	if (man->time_to_sleep < 60)
		return (1);
	if (man->is_must_eat && man->number_of_times_each_philosopher_must_eat < 1)
		return (1);
	return (0);
}

void	ph_init_man(t_man *man, int argc, char *argv[])
{
	man->ate_cnt = NULL;
	man->eat_cnt = 0;
	man->fin = NULL;
	man->id = 0;
	man->lasteat = 0;
	man->left = NULL;
	man->is_must_eat = false;
	man->number_of_times_each_philosopher_must_eat = 0;
	man->right = NULL;
	man->number_of_philosophers = ft_atoi(argv[1]);
	man->time_to_die = ft_atoi(argv[2]);
	man->time_to_eat = ft_atoi(argv[3]);
	man->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		man->is_must_eat = true;
		man->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
}

int ph_solo(t_man *man)
{
	long long	start;

	start = get_mtime();
	printf("%lld %d %s\n", start, 0, PFORK);
	printf("%lld %d %s\n", start + man->time_to_die, 0, PDIED);
	return (0);
}

int	ph_init_arg(int argc, char *argv[], t_philo *ph)
{
	int i;
	t_man	man;

	if (argc != 5 && argc != 6)
		return (ft_error(USAARG));
	ph->number_of_philosophers = ft_atoi(argv[1]);
	ph_init_man(&man, argc, argv);
	if (input_check(&man, ph->number_of_philosophers))
		return (ft_error(USAVAL));
	if (ph->number_of_philosophers == 1)
		exit(ph_solo(&man));
	ph->men = (t_man*)malloc(sizeof(t_man) * ph->number_of_philosophers);
	if (!ph->men)
		return (ft_error(EMALLOC));
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		man.id = i + 1;
		ph->men[i] = man;
		ph->men[i].fin = &ph->fin;
	}
	return (0);
}