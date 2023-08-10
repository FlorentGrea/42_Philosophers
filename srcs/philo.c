/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:50:55 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/18 18:04:00 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ph_error()
{
	if (errno == 0)
		printf("Wrong arguments\n");
	else
		perror(strerror(errno));
	exit(0);
}

void	ph_check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		ph_error();
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
			if (av[i][j] < '0' || av[i][j++] > '9')
				ph_error();
	}
}

t_sets	ph_get_static_data(int ac, char **av)
{
	t_sets		data;
	//pthread_mutex_t	talk;
	int		i;

	if (ft_atoi(av[1]) <= 0)
		ph_error();
	if (ac < 6)
		data.must_eat = -1;
	else
		data.must_eat = ft_atoi(av[5]);
	data.t_sleep = ft_atoi(av[4]);
	data.t_eat = ft_atoi(av[3]);
	data.t_die = ft_atoi(av[2]);
	data.n_philo = ft_atoi(av[1]);
	data.start_time = ph_get_time();
	data.talk = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(data.talk, NULL))
		ph_error();
	//*data.talk = talk;
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
			data.n_philo);
	if (!data.forks)
		ph_error();
	i = 0;
	while (i < data.n_philo)
		if (pthread_mutex_init(&data.forks[i++], NULL))
			ph_error();
	return (data);
}

t_sets	*ph_get_data(int ac, char **av)
{
	t_sets			*ret;
	t_sets			data;
	int				i;

	data = ph_get_static_data(ac, av);
	ret = (t_sets *)malloc(sizeof(t_sets) * data.n_philo);
	if (!ret)
		ph_error();
	i = -1;
	while (++i < data.n_philo)
	{
		ret[i] = data;
		ret[i].nbr = i;
	}
	return (ret);
}

int	main(int ac, char **av)
{
	t_sets	*data;

	//check args
	ph_check_args(ac, av);

	//get data
	data = ph_get_data(ac, av);
	printf("n_philo = %d\n", data->n_philo);
	printf("t_die = %d\n", data->t_die);
	printf("t_eat = %d\n", data->t_eat);
	printf("t_sleep = %d\n", data->t_sleep);
	printf("start_time = %d\n", data->start_time);
	printf("must_eat = %d\n", data->must_eat);

	//launching logic
	ph_logic(data);
	return (0);
}
