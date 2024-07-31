#include "philo.h"
/* grimreaper()
check for deaths or full philos 
call this in a seperate thread or in the main program
*/

t_bool is_end(t_philo *philo)
{
	t_bool end_val;
	pthread_mutex_lock(&philo->end_mtx);
	end_val = FALSE;
	if (philo->start_time - philo->last_meal_time >= philo->arg.time_to_die)
	{
		end_val = TRUE;
		philo->end_sig = DEAD;
	}
	if (philo->arg.left_meals <= 0)
		philo->end_sig = NO_MEALS_LEFT;
	pthread_mutex_unlock(&philo->end_mtx);
	return(end_val);
}

int grim_reaper(t_philo *all_philos)
{
	int idx;
	int full_philos;

	full_philos = 0;
	idx = -1;
	while (++idx < all_philos->arg.philo_count)
	{
		if (is_end(&all_philos[idx]))
		{
			if (all_philos[idx].end_sig == DEAD)
				//log death;
			else
				full_philos++;
		}
	}
	if (full_philos == all_philos->arg.philo_count)
	{
		// stop sim;
	}
	return (EXIT_SUCCESS);
}