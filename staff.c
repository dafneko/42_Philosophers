#include "philo.h"
/* grimreaper()
check for deaths or full philos 
call this in a seperate thread or in the main program
*/

t_bool detect_death(t_philo *philo)
{
	t_bool end_val;
	t_ll cur_time;
	
	end_val = FALSE;
	cur_time = look_at_clock();
	if (cur_time - philo->last_meal_time >= philo->arg.time_to_die)
	{
		end_val = TRUE;
	}
	return(end_val);
}

int grim_reaper(t_philo *all_philos)
{
	int idx;

	idx = -1;
	while (++idx < all_philos->arg.philo_count)
	{
		if (detect_death(&all_philos[idx]))
		{
			//log
			// pthread_mutex_lock(all_philos[idx].arg.end_mtx);
			*(all_philos[idx].end_sig) = DEAD;
			life_updates(&all_philos[idx], DEAD);
			break;
			// pthread_mutex_unlock(all_philos[idx].arg.end_mtx);
		}
	}
	return (EXIT_SUCCESS);
}

t_bool is_end(t_philo *philo)
{
	t_bool end_val;
	
	end_val = FALSE;
	// pthread_mutex_lock(philo->arg.end_mtx);
	if (*(philo->end_sig))
		end_val = TRUE;
	// pthread_mutex_unlock(philo->arg.end_mtx);
	if (!philo->arg.left_meals)
		end_val = TRUE;
	return (end_val);
}

void life_updates(t_philo *philo, int status)
{
	int current_time;
	// pthread_mutex_lock(philo->arg.end_mtx);
	current_time = look_at_clock();
	if (status == THINK)
	{
		printf("%i %i is thinking\n",current_time, philo->id);
	}
	else if (status == EAT)
	{
		printf("%i %i is eating\n", current_time, philo->id);
	}
	else if (status == SLEEP)
	{
		printf("%i %i is sleeping\n", current_time, philo->id);
	}
	else if (status == DEAD)
	{
		printf("%i %i died\n", current_time, philo->id);
	}
	// pthread_mutex_unlock(philo->arg.end_mtx);
}
