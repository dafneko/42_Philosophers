#include "philo.h"

// think
int ithink_therefore_iam(t_philo *philo)
{
	// log thinking
	//usleep time to think

}
// eat
int have_a_feast(t_philo *philo)
{
	
}
// sleep
int rest(t_philo *philo)
{
	// log sleeping
	//sleep
}
// full routine

void daily_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	//get start time
	philo->start_time = look_at_clock();
	philo->last_meal_time = philo->start_time;
	
	//loop while no death and no one is full
	//think
	//eat
	//sleep
}