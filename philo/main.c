/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:55:33 by hdurand           #+#    #+#             */
/*   Updated: 2021/10/18 14:55:35 by hdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*ft_thread(void *philo)
{
	t_philo		*phi;

	phi = (t_philo *)philo;
	if (phi->tid % 2 == 0)
		usleep(1);
	pthread_mutex_lock(phi->die_mutex);
	while (*(phi->has_died) == 0)
	{
		pthread_mutex_unlock(phi->die_mutex);
		ft_eat(phi);
		pthread_mutex_lock(phi->clockmutex);
		*(phi->meal_count) += 1;
		if (*(phi->meal_count) == phi->max_meal && phi->max_meal != 0)
			break ;
		pthread_mutex_unlock(phi->clockmutex);
		ft_sleep(phi);
		ft_think(phi);
	}
	if (*(phi->has_died) != 0)
		pthread_mutex_unlock(phi->die_mutex);
	if (phi->max_meal != 0)
		pthread_mutex_unlock(phi->clockmutex);
	pthread_exit(NULL);
}

void	ft_exit_clean(t_info *info, pthread_t *threads, t_philo *phi)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		pthread_join(threads[i], NULL);
	free(threads);
	i = -1;
	while (++i < info->philo_num)
		pthread_mutex_destroy(&info->clock.clockmutexes[i]);
	i = -1;
	while (++i < info->philo_num)
		pthread_mutex_destroy(&info->forks[i]);
	free(info->forks);
	pthread_mutex_destroy(&info->clock.die_mutex);
	free(info->clock.clockmutexes);
	free(info->clock.meal_count);
	free(info->clock.last_meals);
	free(info->start);
	i = -1;
	while (++i < info->philo_num)
		free(phi[i].forksnum);
	free(phi);
}

void	ft_manager(t_info *info)
{
	pthread_t	*threads;
	t_philo		*phi;
	int			i;
	long		ct;

	i = -1;
	phi = malloc(sizeof(*phi) * (info->philo_num));
	while (++i < info->philo_num)
		phi[i] = ft_collect_philo(info, i);
	threads = malloc(sizeof(pthread_t) * info->philo_num);
	ct = ft_get_time();
	i = -1;
	while (++i < info->philo_num)
	{
		phi[i].start = ct;
		if (pthread_create(&threads[i], NULL, ft_thread, (void *)&phi[i]) != 0)
			printf("shiiiit\n");
	}
	info->clock.start = ct;
	if (info->eat_limit == 0)
		ft_clockworks(&info->clock);
	else
		ft_double_clock(&info->clock);
	ft_exit_clean(info, threads, phi);
}

int	main(int ac, char **av)
{
	t_info	*info;
	long	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (0);
	if (ft_collect_info(ac, av, info) == 0)
		return (0);
	ft_manager(info);
	free(info);
	return (0);
}
