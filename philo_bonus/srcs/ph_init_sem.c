/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_sem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:06:07 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 11:05:39 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

sem_t	*ph_semset(const char *src, int value, int id)
{
	sem_t	*ret;
	char	*name;
	char	*saf;
	char	*tmp;

	name = ft_strdup(src);
	if (!name)
		exit(ft_error(EMALLOC));
	if (id > 0)
	{
		saf = ft_itoa(id);
		if (!saf)
			exit(ft_error(EMALLOC));
		tmp = name;
		name = ft_strjoin(name, saf);
		if (!name)
			exit(ft_error(EMALLOC));
		free(saf);
		free(tmp);
	}
	sem_unlink(name);
	ret = sem_open(name, O_CREAT, 0600, value);
	sem_unlink(name);
	free(name);
	return (ret);
}

int	ph_init_sem(t_philo *ph)
{
	int	i;

	ph->pout = ph_semset("/pout", 1, 0);
	ph->men[0].fork = ph_semset("/fork", ph->number_of_philosophers, 0);
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		ph->men[i].pout = ph->pout;
		ph->men[i].fork = ph->men[0].fork;
		ph->men[i].eat = ph_semset("/eat_", 0, ph->men[i].id);
	}
	i = -1;
	return (0);
}
