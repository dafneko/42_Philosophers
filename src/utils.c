/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:37 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/09 03:42:09 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	len_check(char *str)
{
	int	len;

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

static int	is_digit(int c)
{
	return ('0' <= c && '9' >= c);
}

int	parse_arguments(char *str, int *ms)
{
	int	nbr;
	int	idx;

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

time_t	look_at_clock(void)
{
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	return (clock.tv_sec * 1000 + clock.tv_usec / 1000);
}

void	life_updates(t_philo *philo, int status)
{
	time_t	current_time;

	current_time = look_at_clock();
	pthread_mutex_lock(philo->arg.logger_mtx);
	if (status == DEAD)
	{
		printf("%li %i died\n", current_time, philo->id);
		pthread_mutex_unlock(philo->arg.logger_mtx);
		return ;
	}
	if (!is_end(philo))
	{
		if (status == THINK)
			printf("%li %i is thinking\n", current_time, philo->id);
		else if (status == EAT)
			printf("%li %i is eating\n", current_time, philo->id);
		else if (status == SLEEP)
			printf("%li %i is sleeping\n", current_time, philo->id);
		else if (status == FORK)
			printf("%li %i has taken a fork\n", current_time, philo->id);
		else if (status == NO_FORK)
			printf("%li %i has put down a fork\n", current_time, philo->id);
	}
	pthread_mutex_unlock(philo->arg.logger_mtx);
}
