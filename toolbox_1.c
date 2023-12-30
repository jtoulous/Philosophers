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

unsigned long	convert_time(unsigned long in_sec, unsigned long in_micro)
{
	unsigned long	converted;

	converted = in_sec * 1000 + in_micro / 1000;
	return (converted);
}

unsigned long	atoul(char *arg)
{
	unsigned long	res;
	int				z;

	res = 0;
	z = 0;
	while (arg[z])
	{
		if (arg[z + 1] == '\0')
			return (res + (arg[z] - '0'));
		else
			res = (res + (arg[z] - '0')) * 10;
		z++;
	}
	return (res);
}

static void	what_he_doing(int act)
{
	if (act == 1)
		printf("is thinking\n");
	if (act == 2)
		printf("has taken a fork\n");
	if (act == 3)
		printf("is eating\n");
	if (act == 4)
		printf("is sleeping\n");
}

void	print_action(int philo, int action, t_data *data)
{
	struct timeval	tv;
	unsigned long	timestamp;
	unsigned long	last_eat;
	unsigned long	time;

	if (get_run_stat(data) != 1)
		return ;
	pthread_mutex_lock(&data->data_mtx);
	last_eat = data->last_kebs[philo];
	pthread_mutex_unlock(&data->data_mtx);
	pthread_mutex_lock(&data->print_mtx);
	gettimeofday(&tv, NULL);
	time = convert_time(tv.tv_sec, tv.tv_usec);
	timestamp = time - data->entry_t;
	if (get_run_stat(data) == 1 && time < last_eat + data->die_t)
	{
		printf("%lu: philo %d ", timestamp, philo + 1);
		what_he_doing(action);
	}
	pthread_mutex_unlock(&data->print_mtx);
}

void	freedom(t_data *data)
{
	if (data->threads != NULL)
		free(data->threads);
	if (data->forks != NULL)
		free(data->forks);
	if (data->nb_kebs != NULL)
		free(data->nb_kebs);
	if (data->last_kebs != NULL)
		free(data->last_kebs);
}
