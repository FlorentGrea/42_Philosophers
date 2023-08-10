/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_needs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:55:29 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/18 18:04:03 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	death = 0;

/*
 *	Handle talking (obviously) but also dying gestion. A mutex is used for 
 *		avoiding a scramble view on the STDOUT.
 */

int	ph_talking(t_sets data, char *str)
{
	pthread_mutex_lock(data.talk);
	if (!death)
	{
		if (ph_get_time() - data.start_time - data.time > data.t_die)
		{
			death = 1;
			printf("%d %d %s", data.time + data.t_die, \
					data.nbr + 1, "died\n");
		}
		else
			printf("%d %d %s", ph_get_time() - data.start_time, \
					data.nbr + 1, str);
	}
	pthread_mutex_unlock(data.talk);
	if (death)
		return (-1);
	return (0);
}

/*
 *	Handle the sleeping and thinking part (what a surprise).
 */

int	ph_sleeping_and_thinking(t_sets data)
{
	int	time;

	if (ph_talking(data, "is sleeping\n"))
		return (-1);
	time = ph_get_time();
	while ((ph_get_time() - time) < data.t_sleep)
		;
	if (ph_talking(data, "is_thinking\n"))
		return (-1);
	return (0);
}

/*
 *	Handle eating part, which is the true challenge of the project.
 */

int	ph_eating(t_sets data)
{
	int	time;

	pthread_mutex_lock(&data.forks[data.nbr]);
	ph_talking(data, "has taken a fork\n");
	pthread_mutex_lock(&data.forks[(data.nbr + 1) % data.n_philo]);
	ph_talking(data, "has taken a fork\n");
	data.time = ph_get_time() - data.start_time;
	ph_talking(data, "is eating\n");
	time = ph_get_time();
	while ((ph_get_time() - time) < data.t_eat)
		;
	pthread_mutex_unlock(&data.forks[data.nbr]);
	pthread_mutex_unlock(&data.forks[(data.nbr + 1) % data.n_philo]);
	return (data.time);
}
