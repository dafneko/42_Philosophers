/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:06:07 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/22 09:52:03 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_and_destroy_mtx(t_philo *philo)
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
	if (philo->arg.meal_mtx)
	{
		pthread_mutex_destroy(philo->arg.meal_mtx);
		free(philo->arg.meal_mtx);
	}
	if (philo->arg.meal_num_mtx)
	{
		pthread_mutex_destroy(philo->arg.meal_num_mtx);
		free(philo->arg.meal_num_mtx);
	}
}

int	free_all(t_philo *philo, pthread_t *philo_th)
{
	int	i;

	i = -1;
	free_and_destroy_mtx(philo);
	while (++i < philo->arg.philo_count)
	{
		if (philo[i].right_fork)
		{
			pthread_mutex_destroy(philo[i].right_fork);
			free(philo[i].right_fork);
		}
	}
	if (philo->end_sig)
		free(philo->end_sig);
	if (philo->start_time)
		free(philo->start_time);
	free(philo);
	free(philo_th);
	return (EXIT_SUCCESS);
}

void	safe_free(t_data *arg)
{
	if (arg->end_mtx)
	{
		pthread_mutex_destroy(arg->end_mtx);
		free(arg->end_mtx);
	}
	if (arg->logger_mtx)
	{
		pthread_mutex_destroy(arg->logger_mtx);
		free(arg->logger_mtx);
	}
	if (arg->meal_mtx)
	{
		pthread_mutex_destroy(arg->meal_mtx);
		free(arg->meal_mtx);
	}
	if (arg->meal_num_mtx)
	{
		pthread_mutex_destroy(arg->meal_num_mtx);
		free(arg->meal_num_mtx);
	}
	if (arg->sim_start)
		free(arg->sim_start);
}
