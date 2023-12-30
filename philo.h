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

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_info
{
	int		nb;
	int		fk_1;
	int		fk_2;
	int		lock_1;
	int		lock_2;
}		t_info;

typedef struct s_data
{
	pthread_t		*threads;
	pthread_t		run_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	data_mtx;
	pthread_mutex_t	run_mtx;
	int				*nb_kebs;
	unsigned long	*last_kebs;
	unsigned long	entry_t;
	unsigned long	die_t;
	unsigned long	eat_t;
	unsigned long	sleep_t;
	int				total_philo;
	int				philo_nb;
	int				run_stat;
	int				max_kebs;
}			t_data;

int				nightclub_security(int argc, char **argv);
void			*run_status(void *argz);
int				init_data(int argc, char **argv, t_data *data, int z);
void			init_philo_data(t_data *data, t_info *philo);
void			*cycle_of_life(void	*argz);
void			print_action(int philo, int action, t_data *data);
unsigned long	convert_time(unsigned long in_sec, unsigned long in_micro);
void			freedom(t_data *data);
unsigned long	atoul(char *arg);
void			*run_status_solo(void *argz);
void			death_check(t_data *data, int z);
int				get_run_stat(t_data *data);

#endif
