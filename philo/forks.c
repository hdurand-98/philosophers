/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:55:15 by hdurand           #+#    #+#             */
/*   Updated: 2021/10/18 14:55:17 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	ft_init_forks(int philo_num, t_info *info)
{
	int	i;

	i = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	while (i < philo_num)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
}

void	ft_let_forks(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

void	ft_take_forks(t_philo *phi)
{
	pthread_mutex_lock(&phi->forks[phi->forksnum[0]]);
	pthread_mutex_lock(phi->clockmutex);
	if (*(phi->has_died) == 0)
		printf("%ld %ld has taken fork\n", ft_get_time() - phi->start, phi->tid);
	pthread_mutex_unlock(phi->clockmutex);
	if (phi->forksnum[1] == -1)
		pthread_exit(NULL);
	pthread_mutex_lock(&phi->forks[phi->forksnum[1]]);
	pthread_mutex_lock(phi->clockmutex);
	if (*(phi->has_died) == 0)
		printf("%ld %ld has taken fork\n", ft_get_time() - phi->start, phi->tid);
	pthread_mutex_unlock(phi->clockmutex);
}
