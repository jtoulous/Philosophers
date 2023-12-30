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

static void	max_kebs_check(t_data *data)
{
	int	z;
	int	nb_kebz;

	z = 0;
	if (get_run_stat(data) != 1)
		return ;
	while (z < data->total_philo)
	{
		pthread_mutex_lock(&data->data_mtx);
		nb_kebz = data->nb_kebs[z];
		pthread_mutex_unlock(&data->data_mtx);
		if (nb_kebz < data->max_kebs)
			return ;
		z++;
	}
	pthread_mutex_lock(&data->print_mtx);
	printf("max reached, philos status: all alive\n");
	data->run_stat = 0;
	pthread_mutex_unlock(&data->print_mtx);
}

void	death_check(t_data *data, int z)
{
	struct timeval	tv;
	unsigned long	time;
	unsigned long	last_eat;

	gettimeofday(&tv, NULL);
	time = convert_time(tv.tv_sec, tv.tv_usec);
	while (++z < data->total_philo && get_run_stat(data) == 1)
	{
		pthread_mutex_lock(&data->data_mtx);
		last_eat = data->last_kebs[z];
		pthread_mutex_unlock(&data->data_mtx);
		if (time >= last_eat + data->die_t
			&& get_run_stat(data) == 1)
		{
			pthread_mutex_lock(&data->print_mtx);
			if (get_run_stat(data) == 1)
				printf("%lu: philo %d is dead\n", time - data->entry_t, z + 1);
			pthread_mutex_lock(&data->run_mtx);
			data->run_stat = 0;
			pthread_mutex_unlock(&data->run_mtx);
			pthread_mutex_unlock(&data->print_mtx);
			return ;
		}
	}
}

int	get_run_stat(t_data *data)
{
	int	rtn_val;

	pthread_mutex_lock(&data->run_mtx);
	rtn_val = data->run_stat;
	pthread_mutex_unlock(&data->run_mtx);
	return (rtn_val);
}

void	*run_status(void *argz)
{
	t_data	*data;

	data = (t_data *)argz;
	while (get_run_stat(data) == 1)
	{
		death_check(data, -1);
		if (data->max_kebs != -1)
			max_kebs_check(data);
	}
	return (NULL);
}
