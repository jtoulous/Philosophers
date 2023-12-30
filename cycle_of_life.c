/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:27:32 by jtoulous          #+#    #+#             */
/*   Updated: 2023/03/15 15:56:57 by jtoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	go_thinking(t_data *data, t_info *philo)
{
	print_action(philo->nb, 1, data);
	pthread_mutex_lock(&data->forks[philo->fk_1]);
	philo->lock_1 = 1;
	print_action(philo->nb, 2, data);
	pthread_mutex_lock(&data->forks[philo->fk_2]);
	philo->lock_2 = 1;
	print_action(philo->nb, 2, data);
}

static void	go_eating(t_data *data, t_info *philo)
{
	struct timeval	tv;
	unsigned long	start;
	unsigned long	actual_time;

	gettimeofday(&tv, NULL);
	start = convert_time(tv.tv_sec, tv.tv_usec);
	actual_time = start;
	pthread_mutex_lock(&data->data_mtx);
	data->last_kebs[philo->nb] = start;
	if (data->max_kebs != -1)
		data->nb_kebs[philo->nb] += 1;
	pthread_mutex_unlock(&data->data_mtx);
	print_action(philo->nb, 3, data);
	while (get_run_stat(data) == 1 && actual_time - start < data->eat_t)
	{
		gettimeofday(&tv, NULL);
		actual_time = convert_time(tv.tv_sec, tv.tv_usec);
	}
	pthread_mutex_unlock(&data->forks[philo->fk_1]);
	philo->lock_1 = 0;
	pthread_mutex_unlock(&data->forks[philo->fk_2]);
	philo->lock_2 = 0;
}

static void	go_sleeping(t_data *data, t_info *philo)
{
	struct timeval	tv;
	unsigned long	start;
	unsigned long	actual_time;

	gettimeofday(&tv, NULL);
	start = convert_time(tv.tv_sec, tv.tv_usec);
	actual_time = start;
	print_action(philo->nb, 4, data);
	while (get_run_stat(data) == 1 && actual_time - start < data->sleep_t)
	{
		gettimeofday(&tv, NULL);
		actual_time = convert_time(tv.tv_sec, tv.tv_usec);
	}
}

void	*cycle_of_life(void *argz)
{
	t_data		*data;
	t_info		philo;

	data = (t_data *)argz;
	init_philo_data(data, &philo);
	if (philo.nb % 2 != 0 || philo.nb == data->total_philo)
		usleep(1000);
	while (get_run_stat(data) == 1)
	{
		if (get_run_stat(data) == 1)
			go_thinking(data, &philo);
		if (get_run_stat(data) == 1)
			go_eating(data, &philo);
		if (get_run_stat(data) == 1)
			go_sleeping(data, &philo);
	}
	if (philo.lock_1 == 1)
		pthread_mutex_unlock(&data->forks[philo.fk_1]);
	if (philo.lock_2 == 1)
		pthread_mutex_unlock(&data->forks[philo.fk_2]);
	return (NULL);
}
