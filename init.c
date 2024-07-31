#include "philo.h"

int check_arg(int ac, char **argv, t_args *arg)
{
	int err;

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
	return (EXIT_SUCCESS);
}

int init_philo(t_philo *philo, t_args *args, int id, t_mutex *other_fork)
{
	// init fork
	pthread_mutex_init(&(philo)->right_fork, NULL);	 
	philo->left_fork = other_fork;
	philo->id = id;
	philo->arg = *args;
	philo->start_time = 0;
	philo->last_meal_time = 0;
	philo->end_sig = FALSE;
	pthread_mutex_init(&philo->logger_mtx, NULL);
	pthread_mutex_init(&philo->end_mtx, NULL);
	return (EXIT_SUCCESS);
}

/*
“I think God, in creating man, somewhat overestimated his ability.”
― Oscar Wilde
*/
static int thus_god_created_man(t_args *args, t_philo all_philos[])
{
	t_philo next_philo;
	t_philo cur_philo;
	int idx;

	init_philo(&cur_philo, args, 0, NULL);
	all_philos[0] = cur_philo;
	idx = -1;
	while (++idx < args->philo_count)
	{
		if ((idx + 1) == args->philo_count)
			init_philo(&next_philo, args, idx + 1, &all_philos[0].right_fork);
		else
		{
			init_philo(&next_philo, args, idx + 1, NULL);
			cur_philo.left_fork = &next_philo.right_fork;
		}
		all_philos[idx] = cur_philo;
		cur_philo = next_philo;
	}
	return (EXIT_SUCCESS);
}
/* thus god created man in his own image, philosophers created god in theirs*/



/* 
“Yes, man is mortal, but that would be only half the trouble. The worst of it is that he's sometimes unexpectedly mortal—there's the trick!”
― Mikhail Bulgakov, The Master and Margarita
*/
int start_lifetime(t_args *args)
{
	t_philo *all_philos;
	printf("philo count = %i\n", args->philo_count);

	all_philos = malloc(sizeof(t_philo) * args->philo_count + 1);
	if (all_philos == NULL)
		return (EXIT_FAILURE);
	memset(all_philos, 0, args->philo_count);
	thus_god_created_man(args, all_philos);
	int idx = -1;
	while (++idx < args->philo_count)
		printf("philo id = %i\n", all_philos[idx].id);
	//grim reaper
	//free and destroy
	// return to main
	free(all_philos);
	return (EXIT_SUCCESS);

}
