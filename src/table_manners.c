/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_manners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:23:17 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/09 00:33:58 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		life_updates(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		life_updates(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		life_updates(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		life_updates(philo, FORK);
	}
}

void	put_down_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		life_updates(philo, NO_FORK);
		pthread_mutex_unlock(philo->left_fork);
		life_updates(philo, NO_FORK);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		life_updates(philo, NO_FORK);
		pthread_mutex_unlock(philo->right_fork);
		life_updates(philo, NO_FORK);
	}
}
