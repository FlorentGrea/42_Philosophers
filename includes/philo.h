#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_sets
{
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		must_eat;
	int		start_time;
	
	int		nbr;
	int		time;

	pthread_mutex_t *talk;
	pthread_mutex_t	*forks;
}	t_sets;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
int	ft_atoi(const char *s);
int	ft_strlen(char *s);

void	ph_error();

int	ph_get_time();

int	ph_talking(t_sets data, char *str);

int	ph_sleeping_and_thinking(t_sets data);
int	ph_eating(t_sets data);

void	ph_logic(t_sets *data);

#endif
