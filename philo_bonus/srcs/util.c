/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:07:31 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 11:04:58 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_preparse(char **str, int *n)
{
	*n = 1;
	while (**str == ' ' || (**str >= 11 && **str <= 15))
		++*str;
	if (**str == '-')
		*n = -1;
	if (**str == '+' || **str == '-')
		++*str;
}

int	ft_atoi(char *nptr)
{
	char		*str;
	int			n;
	int			num;
	long long	m;

	if (!nptr)
		return (0);
	str = (char *)nptr;
	ft_preparse(&str, &n);
	m = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = (*str++ - '0');
		if ((m >= 922337203685477580 && num > 7) || m >= 922337203685477581)
			return (-1);
		if ((m <= -922337203685477580 && num > 8) || m <= -922337203685477581)
			return (0);
		m = m * 10 + n * num;
	}
	return (m);
}

long long	get_mtime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}
