#include "philo.h"


void pickup_fork(t_philo *philo, int dom_hand)
{
	if (dom_hand == RIGHTIE)
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
	}
}

void put_down_fork(t_philo *philo, int dom_hand)
{
	if (dom_hand == RIGHTIE)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

int ithink_therefore_iam(t_philo *philo)
{
	life_updates(philo, THINK);
	return (EXIT_SUCCESS);
}

int have_a_feast(t_philo *philo, int dom_hand)
{
	// pickup_fork(philo, dom_hand);
	(void)dom_hand;
	life_updates(philo, EAT);
	usleep(philo->arg.eat_micro);
	// put_down_fork(philo, dom_hand);
	return (EXIT_SUCCESS);
}

int rest(t_philo *philo)
{
	(void)philo;
	life_updates(philo, SLEEP);
	usleep(philo->arg.sleep_micro);
	return (EXIT_SUCCESS);
}

void daily_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	//get start time
	philo->start_time = look_at_clock();
	philo->last_meal_time = philo->start_time;
	int i = 0;
	while (!is_end(philo) && i < 1)
	{
		ithink_therefore_iam(philo);
		if (philo->id == 2)
			have_a_feast(philo, RIGHTIE);
		else
			have_a_feast(philo, LEFTIE);
		rest(philo);
		i++;
		/* code */
	}
	
	//loop while no death and no one is full
	//think
	//eat
	//sleep
}