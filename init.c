#include "philo.h"

int check_arg(int ac, char **argv, t_args *arg)
{
	int err;

	// printf("ac = %i\n", ac);
	if ((ac < 5 || ac > 6))
		return (EXIT_FAILURE);
	ac--;
	err = FALSE;
	err |= parse_arguments(argv[1], &(arg)->philo_count);
	if (arg->philo_count < 1)
		return (EXIT_FAILURE);
	err |= parse_arguments(argv[2], &(arg)->time_to_die);
	err |= parse_arguments(argv[3], &(arg)->time_to_eat);
	err |= parse_arguments(argv[4], &(arg)->time_to_sleep);
	arg->left_meals = -1;
	if (ac == 5)
		err |= parse_arguments(argv[5], &(arg)->left_meals);
	if (err == TRUE)
		return (EXIT_FAILURE);	
	// printf("philo = %i\n", arg->philo_count);
	// printf("die = %i\n", arg->time_to_die);
	// printf("eat = %i\n", arg->time_to_eat);
	// printf("sleep = %i\n", arg->time_to_sleep);
	// printf("meal count = %i\n", arg->num_of_meals);
	// printf("error = %i\n", err);
	return (EXIT_SUCCESS);
}


// int init_fork(t_mutex *fork)
// {
// 
// }

int init_philo(t_philo *philo, t_args *args, int id, t_mutex *other_fork)
{
	// init fork
	pthread_mutex_init(&(philo)->right_fork, NULL);	 
	philo->left_fork = other_fork;
	philo->arg = *args;
	philo->start_time = 0;
	philo->last_meal_time = 0;
	philo->id = id;
	return (EXIT_SUCCESS);
}

/*
*/

/* initialize chopsticks
// init mutex
*/
/*
“I think God, in creating man, somewhat overestimated his ability.”
― Oscar Wilde*/
// birth philos
static int thus_god_created_man(t_args *args, t_philo all_philos[], pthread_t threads[])
{
	// t_philo philo;
	t_philo next_philo;
	t_philo cur_philo;
	int idx;

	(void)threads;
	init_philo(&cur_philo, args, 0, NULL);
	all_philos[0] = cur_philo;
	idx = -1;
	// printf("philo count = %i\n", args->philo_count);

	while (++idx < args->philo_count)
	{
		// printf("idx = %i and philo id = %i\n", idx, all_philos[idx].id);
		printf("cur philo id = %i\n", cur_philo.id);
		if ((idx + 1) == args->philo_count)
			init_philo(&next_philo, args, idx + 1, &all_philos[0].right_fork);
		else
		{
			init_philo(&next_philo, args, idx + 1, NULL);
			// printf("next id = %i\n", next_philo.id);
			cur_philo.left_fork = &next_philo.right_fork;
		}

		all_philos[idx] = cur_philo;

		cur_philo = next_philo;
		printf("idx = %i and philo id = %i\n", idx, all_philos[idx].id);
		// create threads and join them;
	}
	
	return (EXIT_SUCCESS);
}
/* thus god created man in his own image, philosophers create god in theirs*/



/* “Yes, man is mortal, but that would be only half the trouble. The worst of it is that he's sometimes unexpectedly mortal—there's the trick!”
― Mikhail Bulgakov, The Master and Margarita */

int start_lifetime(t_args *args)
{
	t_philo all_philos[args->philo_count + 1];
	pthread_t threads[args->philo_count];
	printf("philo count = %i\n", args->philo_count);

	thus_god_created_man(args, all_philos, threads);
	int idx = -1;
	while (++idx < args->philo_count)
		printf("philo id = %i\n", all_philos[idx].id);
	// thus god created men
	//grim reaper
	//free and destroy
	// return to main
	return (EXIT_SUCCESS);

}
