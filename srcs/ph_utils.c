#include <philo.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + 48, fd);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int 	ft_atoi(const char *str)
{
	int	ret;
	int	neg;

	ret = 0;
	if (!str)
		return (0);
	if (*str == '-')
		neg = -1;
	else
		neg = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
		ret = (ret * 10) + (*str++ - 48);
	return (ret * neg);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	return ((*s1 && *s2 && *s1 == *s2 && n > 0) ? \
		ft_strncmp(++s1, ++s2, --n) : \
		(unsigned char)(*s1) - (unsigned char)(*s2));
}
