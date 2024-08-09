/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:29 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/09 03:14:29 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* grimreaper()
check for deaths or full philos
call this in a seperate thread or in the main program
*/

t_bool	detect_death(t_philo *philo)
{
	t_bool	end_val;
	time_t	cur_time;

	end_val = FALSE;
	cur_time = look_at_clock();
	pthread_mutex_lock(philo->arg.meal_mtx);
	if ((int)cur_time - (int)philo->last_meal_time >= philo->arg.time_to_die)
		end_val = TRUE;
	pthread_mutex_unlock(philo->arg.meal_mtx);
	return (end_val);
}

int	stop_simulation(t_philo *all_philos, int idx, int full)
{
	while (++idx < all_philos->arg.philo_count)
	{
		pthread_mutex_lock(all_philos[idx].arg.meal_num_mtx);
		if (detect_death(all_philos + idx)
			&& all_philos[idx].arg.left_meals != 0)
		{
			pthread_mutex_unlock(all_philos[idx].arg.meal_num_mtx);
			pthread_mutex_lock(all_philos[idx].arg.end_mtx);
			*(all_philos[idx].end_sig) = DEAD;
			pthread_mutex_unlock(all_philos[idx].arg.end_mtx);
			life_updates(all_philos + idx, DEAD);
			return (EXIT_SUCCESS);
		}
		pthread_mutex_unlock(all_philos[idx].arg.meal_num_mtx);
		pthread_mutex_lock(all_philos[idx].arg.meal_num_mtx);
		if (all_philos[idx].arg.left_meals == 0 && full++)
		{
			if (full == all_philos[idx].arg.philo_count - 1)
			{
				pthread_mutex_unlock(all_philos[idx].arg.meal_num_mtx);
				return (EXIT_SUCCESS);
			}
		}
		pthread_mutex_unlock(all_philos[idx].arg.meal_num_mtx);
	}
	return (EXIT_FAILURE);
}

int	grim_reaper(t_philo *all_philos)
{
	int	idx;
	int	full;

	pthread_mutex_lock(all_philos->arg.meal_num_mtx);
	if (all_philos->arg.left_meals == 0)
	{
		pthread_mutex_unlock(all_philos->arg.meal_num_mtx);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(all_philos->arg.meal_num_mtx);
	while (42)
	{
		full = 0;
		idx = -1;
		usleep(500);
		if (stop_simulation(all_philos, idx, full) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

t_bool	is_end(t_philo *philo)
{
	t_bool	end_val;

	end_val = FALSE;
	pthread_mutex_lock(philo->arg.end_mtx);
	if (*(philo->end_sig))
		end_val = TRUE;
	pthread_mutex_unlock(philo->arg.end_mtx);
	pthread_mutex_lock(philo->arg.meal_num_mtx);
	if (philo->arg.left_meals == 0)
		end_val = TRUE;
	pthread_mutex_unlock(philo->arg.meal_num_mtx);
	return (end_val);
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
