/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:55:51 by hdurand           #+#    #+#             */
/*   Updated: 2021/10/18 14:55:53 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_clock
{
	long			start;
	long			*last_meals;
	int				*meal_count;
	int				max_meal;
	int				ttd;
	int				died;
	int				philo_num;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	*clockmutexes;
}				t_clock;

typedef struct s_info
{
	int				philo_num;
	int				sleep_time;
	int				eat_time;
	int				time_to_die;
	int				eat_limit;
	int				philo_count;
	long			*start;
	int				ready;
	t_clock			clock;

	pthread_mutex_t	*forks;
}				t_info;

typedef struct s_philo
{
	long			tid;
	int				tts;
	int				tte;
	int				ttd;
	int				*forksnum;
	int				state;
	int				*has_died;
	long			start;
	long			*last_meal;
	int				max_meal;
	int				*meal_count;

	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*clockmutex;
	pthread_mutex_t	*forks;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_collect_info(int ac, char **av, t_info *info);
t_philo	ft_collect_philo(t_info *info, int i);
void	ft_let_forks(pthread_mutex_t *fork1, pthread_mutex_t *fork2);
void	ft_init_forks(int philo_num, t_info *info);
void	ft_take_forks(t_philo *phi);
long	ft_get_time(void);
long	ft_get_tid(t_info *inf, int *forksnum);
t_clock	ft_init_clock(int TTD, int ph_num, int max_meal);
void	ft_eat(t_philo *phi);
void	ft_sleep(t_philo *phi);
void	ft_think(t_philo *phi);
void	ft_slip(int sleep_duration, long nap_start, long start);
void	ft_print_state(char *str, int time, int num, int has_died);
int		ft_clockworks(t_clock *clinf);
int		ft_double_clock(t_clock *clinf);
int		ft_isdigit(const char *str);

#endif
