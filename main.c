#include "philo.h"

/*
arguments: ./philo num_of_philos time_to_die time_to_eat time_to_sleep  num_of_meals (optional)
*/


int main(int ac, char **argv)
{
	t_data arg;

    // check args
	if (init_data(ac, argv, &arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
    // start simulation
	start_lifetime(&arg);
    //monitor death or full philos
	return (EXIT_SUCCESS);
}