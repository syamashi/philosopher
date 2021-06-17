/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:04:19 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 12:26:45 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_error(char *mes)
{
	printf("%s\n", mes);
	return (1);
}

int	ph_pout(t_man *man, char *mes)
{
	sem_wait(man->pout);
	printf("%lld %d %s\n", get_mtime(), man->id, mes);
	sem_post(man->pout);
	return (0);
}

int	ph_pout_died(t_man *man, char *mes)
{
	sem_wait(man->pout);
	printf("%lld %d %s\n", get_mtime(), man->id, mes);
	exit(0);
	return (0);
}
