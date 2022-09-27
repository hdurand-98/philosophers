/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:55:10 by hdurand           #+#    #+#             */
/*   Updated: 2021/10/18 14:55:12 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_wrong_arg(t_info *info)
{
	free(info);
	printf("Wrong arguments\n");
	return (0);
}

int	ft_collect_info(int ac, char **av, t_info *info)
{
	info->philo_num = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (info->philo_num <= 0 || info->time_to_die <= 0
		|| info->eat_time <= 0 || info->sleep_time <= 0)
		return (ft_wrong_arg(info));
	info->eat_limit = 0;
	if (ac == 6)
	{
		info->eat_limit = ft_atoi(av[5]);
		if (info->eat_limit <= 0)
			return (ft_wrong_arg(info));
	}
	ft_init_forks(info->philo_num, info);
	info->philo_count = 1;
	info->ready = 0;
	info->start = malloc(sizeof(long));
	*(info->start) = 0;
	info->clock = ft_init_clock
		(info->time_to_die, info->philo_num, info->eat_limit);
	return (1);
}

t_philo	ft_collect_philo(t_info *info, int i)
{
	t_philo	phi;

	phi.forksnum = malloc(sizeof(int) * 2);
	phi.tid = ft_get_tid(info, phi.forksnum);
	if (info->philo_num == 1)
		phi.forksnum[1] = -1;
	phi.tts = info->sleep_time;
	phi.tte = info->eat_time;
	phi.ttd = info->time_to_die;
	phi.state = 0;
	phi.die_mutex = &info->clock.die_mutex;
	phi.forks = info->forks;
	phi.start = 0;
	phi.has_died = &info->clock.died;
	phi.max_meal = info->eat_limit;
	phi.meal_count = &info->clock.meal_count[i];
	*phi.meal_count = 0;
	phi.last_meal = &info->clock.last_meals[i];
	*phi.last_meal = 0;
	phi.clockmutex = &info->clock.clockmutexes[i];
	return (phi);
}

t_clock	ft_init_clock(int TTD, int ph_num, int max_meal)
{
	t_clock	clo;
	int		i;

	i = 0;
	clo.philo_num = ph_num;
	clo.last_meals = malloc(sizeof(long) * ph_num);
	clo.meal_count = malloc(sizeof(int) * ph_num);
	clo.max_meal = max_meal;
	clo.ttd = TTD;
	clo.died = 0;
	clo.start = 0;
	pthread_mutex_init(&clo.die_mutex, NULL);
	clo.clockmutexes = malloc(sizeof(pthread_mutex_t) * ph_num);
	while (i < ph_num)
	{
		pthread_mutex_init(&clo.clockmutexes[i], NULL);
		i++;
	}
	return (clo);
}

long	ft_get_tid(t_info *inf, int *forksnum)
{
	long	tid;

	tid = inf->philo_count;
	inf->philo_count++;
	if (tid == 1)
	{
		forksnum[0] = tid - 1;
		forksnum[1] = inf->philo_num - 1;
	}
	else
	{
		if (tid % 2 == 0)
		{
			forksnum[0] = tid - 2;
			forksnum[1] = tid - 1;
		}
		else
		{
			forksnum[0] = tid - 1;
			forksnum[1] = tid - 2;
		}
	}
	return (tid);
}
