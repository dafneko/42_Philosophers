/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:32 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/09 03:08:05 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ithink_therefore_iam(t_philo *philo)
{
	life_updates(philo, THINK);
	usleep(500);
	return (EXIT_SUCCESS);
}

int	have_a_feast(t_philo *philo)
{
	pickup_fork(philo);
	pthread_mutex_lock(philo->arg.meal_mtx);
	philo->last_meal_time = look_at_clock();
	pthread_mutex_unlock(philo->arg.meal_mtx);
	life_updates(philo, EAT);
	pthread_mutex_lock(philo->arg.meal_num_mtx);
	philo->arg.left_meals--;
	pthread_mutex_unlock(philo->arg.meal_num_mtx);
	usleep(philo->arg.eat_micro);
	put_down_fork(philo);
	return (EXIT_SUCCESS);
}

int	rest(t_philo *philo)
{
	life_updates(philo, SLEEP);
	usleep(philo->arg.sleep_micro);
	return (EXIT_SUCCESS);
}

void	*daily_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->arg.meal_mtx);
	philo->last_meal_time = *philo->start_time;
	pthread_mutex_unlock(philo->arg.meal_mtx);
	while (!is_end(philo))
	{
		ithink_therefore_iam(philo);
		if (philo->left_fork != NULL)
			have_a_feast(philo);
		rest(philo);
	}
	return (EXIT_SUCCESS);
}
