#include "philo.h"

int check_arg(int ac, char **argv, t_args *arg)
{
	int err;

	printf("ac = %i\n", ac);
	if ((ac < 5 || ac > 6))
		return (EXIT_FAILURE);
	ac--;
	arg = malloc(sizeof(t_args) * 1);
	if (arg == NULL)
		return (EXIT_FAILURE);
	memset(arg, 0, sizeof(t_args));
	err = FALSE;
	err |= parse_params(argv[1], &(arg)->philo_count);
	if (arg->philo_count < 1)
		return (EXIT_FAILURE);
	err |= parse_params(argv[2], &(arg)->time_to_die);
	err |= parse_params(argv[3], &(arg)->time_to_eat);
	err |= parse_params(argv[4], &(arg)->time_to_sleep);
	arg->num_of_meals = -1;
	if (ac == 5)
		err |= parse_params(argv[5], &(arg)->num_of_meals);
	if (err == TRUE)
		return (EXIT_FAILURE);	
	// printf("philo = %i", arg->philo_count);
	// printf("die = %i", arg->time_to_die);
	// printf("eat = %i", arg->time_to_eat);
	// printf("sleep = %i", arg->time_to_sleep);
	// printf("meal count = %i", arg->num_of_meals);
	// printf("error = %i", err);
	return (EXIT_SUCCESS);
}
/*
*/

/* initialize chopsticks
// init mutex
*/

/* thus_god_created_man()
//initialize philos

*/