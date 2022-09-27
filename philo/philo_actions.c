/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:55:44 by hdurand           #+#    #+#             */
/*   Updated: 2021/10/18 14:55:45 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	ft_eat(t_philo *phi)
{
	long	currenttime;

	ft_take_forks(phi);
	currenttime = ft_get_time() - phi->start;
	pthread_mutex_lock(phi->clockmutex);
	*(phi->last_meal) = currenttime;
	pthread_mutex_unlock(phi->clockmutex);
	pthread_mutex_lock(phi->die_mutex);
	ft_print_state("eating", currenttime, phi->tid, *(phi->has_died));
	pthread_mutex_unlock(phi->die_mutex);
	ft_slip(phi->tte, currenttime, phi->start);
	ft_let_forks(&phi->forks[phi->forksnum[0]], &phi->forks[phi->forksnum[1]]);
}

void	ft_sleep(t_philo *phi)
{
	long	currenttime;

	currenttime = ft_get_time() - phi->start;
	pthread_mutex_lock(phi->die_mutex);
	ft_print_state("sleeping", currenttime, phi->tid, *(phi->has_died));
	pthread_mutex_unlock(phi->die_mutex);
	ft_slip(phi->tts, currenttime, phi->start);
}

void	ft_think(t_philo *phi)
{
	long	currenttime;

	currenttime = ft_get_time() - phi->start;
	pthread_mutex_lock(phi->die_mutex);
	ft_print_state("thinking", currenttime, phi->tid, *(phi->has_died));
	pthread_mutex_unlock(phi->die_mutex);
	pthread_mutex_lock(phi->die_mutex);
}

void	ft_slip(int sleep_duration, long nap_start, long start)
{
	while (ft_get_time() - start - nap_start < sleep_duration)
		usleep(500);
}

void	ft_print_state(char *str, int time, int num, int has_died)
{
	if (has_died == 0)
		printf("%d %d is %s\n", time, num, str);
}
