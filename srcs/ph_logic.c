/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_logic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:32:10 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/18 18:03:58 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
 *	This fonction give a better precision, it converts and assembles 
 *		seconds and microseconds given by gettimeofday() for more details on 
 *		actual time.
 */

int	ph_get_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ph_error();
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 *	Function for the case of 1 philo, it kill it in a safe way.
 */

void	*ph_kill_the_philo(t_sets data)
{
	pthread_mutex_lock(&data.forks[data.nbr]);
	ph_talking(data, "has taken a fork\n");
	while ((ph_get_time() - data.start_time) < data.t_die)
		;
	ph_talking(data, "died\n");
	return (NULL);
}

/*
 *	Routine function for each thread.
 *	the philosophers waits till they are all set up.
 */

void	*ph_life(void *arg)
{
	t_sets	data;

	data = *(t_sets *)(arg);
	data.time = 0;
	while (ph_get_time() - data.start_time < (data.n_philo * 100))
		;
	if ((data.nbr % 2))
		usleep(500);
	data.start_time = ph_get_time();
	if (data.n_philo == 1)
		return (ph_kill_the_philo(data));
	while (data.must_eat != 0)
	{
		data.time = ph_eating(data);
		if (data.time < 0)
			break;
		if (data.must_eat > 0)
			data.must_eat--;
		if (ph_sleeping_and_thinking(data))
			break;
	}
	return (NULL);
}

/*
 *	The logic function of our program, it launches the threads.
 */

void	ph_logic(t_sets *data)
{
	pthread_t	*thread_ids;
	int		i;

	thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philo);
	if (thread_ids == NULL)
		ph_error();
	i = -1;
	while (++i < data->n_philo)
		if (pthread_create(&thread_ids[i], NULL, &ph_life, &data[i]))
			ph_error();
	i = 0;
	while (i < data->n_philo)
		if (pthread_join(thread_ids[i++], NULL))
			ph_error();
	free(thread_ids);
	free(data->forks);
	free(data);
}
