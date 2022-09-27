/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:55:03 by hdurand           #+#    #+#             */
/*   Updated: 2021/10/18 16:19:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_clockworks(t_clock *clinf)
{
	long	currenttime;
	int		i;

	while (1)
	{
		i = 0;
		currenttime = ft_get_time() - clinf->start;
		while (i < clinf->philo_num)
		{
			pthread_mutex_lock(&clinf->clockmutexes[i]);
			if (currenttime - clinf->last_meals[i] > clinf->ttd)
			{
				pthread_mutex_lock(&clinf->die_mutex);
				clinf->died = 1;
				pthread_mutex_unlock(&clinf->die_mutex);
				printf("philo %d died at %ld\n", i + 1, currenttime);
				pthread_mutex_unlock(&clinf->clockmutexes[i]);
				return (-1);
			}
			pthread_mutex_unlock(&clinf->clockmutexes[i]);
			i++;
		}
	}
}

int	ft_philo_d_or_f(t_clock *clinf, long currentTime, int i, int *fullcount)
{
	if (clinf->meal_count[i] < clinf->max_meal)
	{
		if (currentTime - clinf->last_meals[i] > clinf->ttd)
		{
			pthread_mutex_lock(&clinf->die_mutex);
			clinf->died = 1;
			pthread_mutex_unlock(&clinf->die_mutex);
			printf("philo %d died at %ld\n", i + 1, currentTime);
			pthread_mutex_unlock(&clinf->clockmutexes[i]);
			return (-1);
		}
		return (0);
	}
	else
	{
		*fullcount += 1;
		return (0);
	}
}

int	ft_double_clock(t_clock *clinf)
{
	long	currenttime;
	int		i;
	int		full_count;

	full_count = 0;
	while (full_count < clinf->philo_num)
	{
		currenttime = ft_get_time() - clinf->start;
		i = 0;
		full_count = 0;
		while (i < clinf->philo_num)
		{
			pthread_mutex_lock(&clinf->clockmutexes[i]);
			if (ft_philo_d_or_f(clinf, currenttime, i, &full_count) == -1)
				return (0);
			pthread_mutex_unlock(&clinf->clockmutexes[i]);
			i++;
		}
	}
	return (0);
}
