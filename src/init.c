/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:26 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/09 03:13:37 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv, t_data *arg, int ac, int err)
{
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

int	init_data(int ac, char **argv, t_data *arg)
{
	int	err;

	if ((ac < 5 || ac > 6))
		return (EXIT_FAILURE);
	ac--;
	err = FALSE;
	err = check_args(argv, arg, ac, err);
	if (err == TRUE)
		return (EXIT_FAILURE);
	arg->eat_micro = arg->time_to_eat * 1000;
	arg->sleep_micro = arg->time_to_sleep * 1000;
	arg->sig = malloc(sizeof(int) * 1);
	if (arg->sig == NULL)
		return (EXIT_FAILURE);
	*(arg->sig) = FALSE;
	arg->end_mtx = malloc(sizeof(t_mutex) * 1);
	arg->logger_mtx = malloc(sizeof(t_mutex) * 1);
	arg->meal_mtx = malloc(sizeof(t_mutex) * 1);
	arg->meal_num_mtx = malloc(sizeof(t_mutex) * 1);
	arg->sim_start = malloc(sizeof(t_mutex) * 1);
	pthread_mutex_init(arg->end_mtx, NULL);
	pthread_mutex_init(arg->logger_mtx, NULL);
	pthread_mutex_init(arg->meal_mtx, NULL);
	pthread_mutex_init(arg->meal_num_mtx, NULL);
	return (EXIT_SUCCESS);
}

int	init_philo(t_philo *philo, t_data *args, int id, t_mutex *other_fork)
{
	philo->right_fork = malloc(sizeof(t_mutex) * 1);
	pthread_mutex_init(philo->right_fork, NULL);
	philo->left_fork = other_fork;
	philo->id = id;
	philo->arg = *args;
	philo->start_time = 0;
	philo->last_meal_time = 0;
	philo->end_sig = args->sig;
	philo->start_time = args->sim_start;
	return (EXIT_SUCCESS);
}

/*
“I think God, in creating man, somewhat overestimated his ability.”
― Oscar Wilde
*/
int	thus_god_created_man(t_data *args, t_philo all_philos[],
		pthread_t *philo_th)
{
	t_philo	*next_philo;
	t_philo	*cur_philo;
	int		idx;

	cur_philo = all_philos + 0;
	init_philo(cur_philo, args, 0, NULL);
	idx = -1;
	while (++idx < args->philo_count - 1)
	{
		next_philo = all_philos + idx + 1;
		if ((idx + 1) == args->philo_count - 1)
			init_philo(next_philo, args, idx + 1, all_philos[0].right_fork);
		else
			init_philo(next_philo, args, idx + 1, NULL);
		cur_philo->left_fork = next_philo->right_fork;
		cur_philo = next_philo;
	}
	idx = -1;
	*args->sim_start = look_at_clock();
	while (++idx < args->philo_count)
		pthread_create(philo_th + idx, NULL, daily_routine, all_philos + idx);
	return (EXIT_SUCCESS);
}
/* thus god created man in his own image, philosophers created god in theirs*/

/*
“Yes, man is mortal,
	but that would be only half the trouble. The worst of it is that
	he's sometimes unexpectedly mortal—there's the trick!”
― Mikhail Bulgakov, The Master and Margarita
*/
int	start_lifetime(t_data *args)
{
	t_philo		*all_philos;
	pthread_t	*philo_th;
	int			idx;

	all_philos = malloc(sizeof(t_philo) * args->philo_count);
	if (all_philos == NULL)
		return (EXIT_FAILURE);
	philo_th = malloc(sizeof(pthread_t) * args->philo_count);
	if (philo_th == NULL)
		return (EXIT_FAILURE);
	memset(all_philos, 0, args->philo_count);
	thus_god_created_man(args, all_philos, philo_th);
	grim_reaper(all_philos);
	idx = -1;
	while (++idx < args->philo_count)
		pthread_join(philo_th[idx], NULL);
	free_all(all_philos, philo_th);
	return (EXIT_SUCCESS);
}
