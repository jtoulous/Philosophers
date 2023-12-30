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

static int	actual_lenght(char *argv)
{
	int	z;
	int	lenght;

	lenght = 0;
	z = 0;
	while ((argv[z] < '0' || argv[z] > '9') && argv[z])
		z++;
	while (argv[z] >= '0' && argv[z] <= '9')
	{
		lenght++;
		z++;
	}
	return (lenght);
}

static int	compare_to_lim(char *argv, const char *lim)
{
	int	z;
	int	y;

	y = 0;
	z = 0;
	while ((argv[y] < '0' || argv[y] > '9') && argv[y])
		y++;
	while (lim[z])
	{
		if (argv[y] < lim[z])
			return (1);
		else if (argv[y] > lim[z])
			return (0);
		z++;
		y++;
	}
	return (1);
}

static int	second_bouncer(char **argv)
{
	int	z;

	z = 1;
	while (argv[z])
	{
		if (argv[z][0] == '\0')
			return (69);
		if (actual_lenght(argv[z]) < 10)
			z++;
		else if (actual_lenght(argv[z]) == 10
			&& compare_to_lim(argv[z], "4294967294") == 1)
			z++;
		else
			return (69);
	}
	return (1);
}

static int	first_bouncer(char **argv, int z, int y)
{
	while (argv[++z])
	{
		while (argv[z][y] == ' ' && argv[z][y])
			y++;
		if (argv[z][y] == '+')
			y++;
		while (argv[z][y])
		{
			if (argv[z][y] == ' ')
			{
				while (argv[z][y])
				{
					if (argv[z][y] != ' ' && argv[z][y] != '\0')
						return (69);
					y++;
				}
			}
			else if (argv[z][y] < '0' || argv[z][y] > '9')
				return (69);
			else
				y++;
		}
		y = 0;
	}
	return (1);
}

int	nightclub_security(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (69);
	if (first_bouncer(argv, 0, 0) != 1)
		return (69);
	if (second_bouncer(argv) != 1)
		return (69);
	return (1);
}
