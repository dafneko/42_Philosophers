#include "philo.h"


void pickup_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

void put_down_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

int ithink_therefore_iam(t_philo *philo)
{
	life_updates(philo, THINK);
	return (EXIT_SUCCESS);
}

int have_a_feast(t_philo *philo)
{
	pickup_fork(philo);
	
	pthread_mutex_lock(philo->arg.meal_mtx);
	philo->last_meal_time = look_at_clock();
	pthread_mutex_unlock(philo->arg.meal_mtx);
	life_updates(philo, EAT);
	usleep(philo->arg.eat_micro);
	put_down_fork(philo);
	return (EXIT_SUCCESS);
}

int rest(t_philo *philo)
{
	life_updates(philo, SLEEP);
	usleep(philo->arg.sleep_micro);
	return (EXIT_SUCCESS);
}

void *daily_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	philo->start_time = look_at_clock();
	pthread_mutex_lock(philo->arg.meal_mtx);
	philo->last_meal_time = philo->start_time;
	pthread_mutex_unlock(philo->arg.meal_mtx);
	while (!is_end(philo))
	{
		ithink_therefore_iam(philo);
		have_a_feast(philo);
		rest(philo);
	}
	return (EXIT_SUCCESS);
}