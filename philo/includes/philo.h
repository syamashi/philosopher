/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:49:01 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/18 10:08:28 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define	USAARG	"[usage]: ./philo <philos> <die> <eat> <sleep> (<must>)"
# define	USAVAL	"[usage]: <philos> 200 people or less, <must> more than 0\
, and <others> 60ms or more"
# define EMALLOC "malloc() failed"
# define EMUTEX "pthread_mutex_init() failed"

# define PFORK "has taken a fork"
# define PEAT "is eating"
# define PTHINK "is thinking"
# define PSLEEP "is sleeping"
# define PDIED "is died"

typedef struct s_man
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	bool			is_must_eat;
	int				eat_cnt;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*died;
	pthread_t		thread;
	bool			*fin;
	int				*ate_cnt;
	long long		lasteat;
	int				id;
}	t_man;

typedef struct s_philo
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	bool			is_must_eat;
	t_man			*men;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	died;
	bool			fin;
	pthread_t		watcher;
	int				ate_cnt;
}	t_philo;

int			ph_init_arg(int argc, char *argv[], t_philo *ph);
int			ph_init_fork(t_philo *ph);
int			ph_init_eat(t_philo *ph);
int			ph_init_man(t_philo *ph);
void		ph_launch(t_philo *ph);
void		*ph_watcher(void *p);

/*
** util
*/

int			ft_error(char *mes);
int			ft_atoi(char *nptr);
int			ph_pout(t_man *man, char *mes);
long long	get_mtime(void);
int			all_free(t_philo *ph);

#endif
