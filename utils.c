#include "philo.h"

// argument checks

static int len_check(char *str)
{
	int len;

	len = 0;
	while (*str)
	{
		str++;
		len++;
		if (len > INT_MAX_LEN)
			return (ERROR);
	}
	return (len);	
}

static int is_digit(int c)
{
	return ('0' <= c && '9' >= c);
}

int parse_arguments(char *str, int *ms)
{
	int nbr;
	int idx;

	idx = 0;
	nbr = 0;
	if (len_check(str) == ERROR)
			return (EXIT_FAILURE);
	if (str[idx] == '+')
		idx++;
	while (str[idx])
	{
		if (is_digit(str[idx]))
			nbr = nbr * 10 + (str[idx] - '0');
		else
			return (EXIT_FAILURE);
		idx++;
	}
	*ms = nbr;
	return (EXIT_SUCCESS);
}


t_ll look_at_clock(void)
{
	struct timeval clock;

	gettimeofday(&clock, NULL);
	return(clock.tv_sec * 1000 + clock.tv_usec / 1000);
}

int free_all(t_philo *philo)
{
	if (philo->arg.logger_mtx)
	{
		pthread_mutex_destroy(philo->arg.logger_mtx);
		free(philo->arg.logger_mtx);
	}
	if (philo->arg.end_mtx)
	{
		pthread_mutex_destroy(philo->arg.end_mtx);
		free(philo->arg.end_mtx);
	}
	if (philo->end_sig)
		free(philo->end_sig);
	free(philo);
	return (EXIT_SUCCESS);
}