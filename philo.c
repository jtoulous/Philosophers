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

static void	*philo_force_one(void *argz)
{
	t_data			*data;
	struct timeval	tv;
	unsigned long	time;

	data = (t_data *)argz;
	gettimeofday(&tv, NULL);
	time = convert_time(tv.tv_sec, tv.tv_usec);
	printf("%lu: philo 1 has taken a fork\n", time - data->entry_t);
	while (time - data->entry_t < data->die_t)
	{
		gettimeofday(&tv, NULL);
		time = convert_time(tv.tv_sec, tv.tv_usec);
	}
	printf("%lu: philo 1 is dead\n", time - data->entry_t);
	return (NULL);
}

static int	solo_philo(char **argv, t_data *data)
{
	struct timeval	tv;
	pthread_t		solo_philo;

	if (atoi(argv[1]) != 1)
		return (69);
	data->total_philo = 1;
	data->die_t = atoul(argv[2]);
	gettimeofday(&tv, NULL);
	data->entry_t = convert_time(tv.tv_sec, tv.tv_usec);
	pthread_create(&solo_philo, NULL, &philo_force_one, (void *)data);
	pthread_join(solo_philo, NULL);
	return (1);
}

static void	go_philosophing(t_data *data)
{
	int	z;

	z = -1;
	pthread_create(&data->run_thread, NULL, &run_status, (void *)data);
	while (++z < data->total_philo)
		pthread_create(&data->threads[z], NULL, &cycle_of_life, (void *)data);
	pthread_join(data->run_thread, NULL);
	z = -1;
	while (++z < data->total_philo)
		pthread_join(data->threads[z], NULL);
	z = -1;
	while (++z < data->total_philo)
		pthread_mutex_destroy(&data->forks[z]);
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->data_mtx);
	pthread_mutex_destroy(&data->run_mtx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (nightclub_security(argc, argv) != 1)
	{	
		printf("little problemo\n");
		return (69);
	}
	if (solo_philo(argv, &data) == 1)
		return (0);
	if (init_data(argc, argv, &data, -1) != 1)
	{
		printf("big problemo\n");
		return (69);
	}
	go_philosophing(&data);
	freedom(&data);
	return (0);
}
