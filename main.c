#include "philo.h"

/*
arguments: ./philo num_of_philos time_to_die time_to_eat time_to_sleep  num_of_meals (optional)
*/


int main(int ac, char **argv)
{
	t_args arg;

    // check args
	if (check_arg(ac, argv, &arg) == EXIT_FAILURE)
	{
		// printf("ret of func = %i\n", check_arg(ac, argv, &arg));
		// TO DO: FREE ALL MEMORY
		return (EXIT_FAILURE);
	}
    // start simulation
    //monitor death or full philos
	return (EXIT_SUCCESS);
}