/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:49:01 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 10:54:08 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

# define	USAARG	"[usage]: ./philo <philos> <die> <eat> <sleep> (<must>)"
# define	USAVAL	"[usage]: <philos> 200 people or less, <must> more than 0\
, and <others> 60ms or more"
# define EMALLOC "malloc() failed"
# define EMUTEX "pthread_mutex_init() failed"
# define EFORK "fork() failed"

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
	int				id;
	sem_t			*fork;
	sem_t			*eat;
	sem_t			*pout; // = 1. 誰かが死んだら出さない。
	pthread_t		thread;
	long long		lasteat;
}	t_man;

typedef struct s_philo
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	bool			is_must_eat;
	t_man			*men;
	int				eat_cnt[210];
	sem_t			*pout; // = 1. 誰かが死んだら出さない。
	pid_t 			pid[210];
	pid_t			pid_watcher;
	pthread_t		eat_watcher;
}	t_philo;

int			ph_init_arg(int argc, char *argv[], t_philo *ph);
int			ph_init_fork(t_philo *ph);
int			ph_init_sem(t_philo *ph);
int			ph_launch(t_philo *ph);
int			ph_launch_fork_philos(t_philo *ph);
void		*ph_watcher(void *p);
int			ph_launch_eat_watcher(t_philo *ph);
void		ph_kill_all(t_philo *ph);
int			ph_pout_died(t_man *man, char *mes);

/*
** util
*/

int			ft_error(char *mes);
int			ft_atoi(char *nptr);
char		*ft_strdup(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);
int			ph_pout(t_man *man, char *mes);
long long	get_mtime(void);
int			all_free(t_philo *ph);

#endif
