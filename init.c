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

static void	b_null(t_data *data)
{
	data->threads = NULL;
	data->forks = NULL;
	data->nb_kebs = NULL;
	data->last_kebs = NULL;
}

static int	init_mutex_n_threads(t_data *data)
{
	int	z;

	z = -1;
	data->threads = calloc(data->total_philo + 1, sizeof(pthread_t));
	if (!data->threads)
		return (0);
	data->forks = calloc(data->total_philo + 1, sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		freedom (data);
		return (0);
	}
	while (++z < data->total_philo)
		pthread_mutex_init(&data->forks[z], NULL);
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->data_mtx, NULL);
	pthread_mutex_init(&data->run_mtx, NULL);
	return (1);
}

static void	argc_six_init(t_data *data, int argc, char **argv)
{
	int	z;

	z = -1;
	if (argc == 6)
	{
		data->max_kebs = atoi(argv[5]);
		data->nb_kebs = calloc(data->total_philo + 1, sizeof(int));
		while (++z < data->total_philo)
			data->nb_kebs[z] = 0;
	}
	else
		data->max_kebs = -1;
}

int	init_data(int argc, char **argv, t_data *data, int z)
{
	struct timeval	tv;

	b_null(data);
	data->total_philo = atoi(argv[1]);
	if (data->total_philo <= 0)
		return (69);
	data->die_t = atoul(argv[2]);
	data->eat_t = atoul(argv[3]);
	data->sleep_t = atoul(argv[4]);
	argc_six_init(data, argc, argv);
	data->philo_nb = 0;
	data->run_stat = 1;
	if (init_mutex_n_threads(data) != 1)
		return (69);
	data->last_kebs = calloc(data->total_philo + 1, sizeof(unsigned long long));
	gettimeofday(&tv, NULL);
	data->entry_t = convert_time(tv.tv_sec, tv.tv_usec);
	while (++z < data->total_philo)
		data->last_kebs[z] = data->entry_t;
	return (1);
}

void	init_philo_data(t_data *data, t_info *philo)
{
	pthread_mutex_lock(&data->data_mtx);
	philo->nb = data->philo_nb;
	data->philo_nb++;
	if (philo->nb == 0)
		philo->fk_1 = data->total_philo - 1;
	else
		philo->fk_1 = philo->nb - 1;
	philo->fk_2 = philo->nb;
	data->last_kebs[philo->nb] = data->entry_t;
	pthread_mutex_unlock(&data->data_mtx);
	philo->fk_2 = philo->nb;
	philo->lock_1 = 0;
	philo->lock_2 = 0;
}
