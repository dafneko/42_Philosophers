/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:26 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/21 04:04:05 by dkoca            ###   ########.fr       */
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

int	init_mtx(t_data *arg)
{
	arg->end_mtx = malloc(sizeof(t_mutex) * 1);
	if (!arg->end_mtx)
		return (safe_free(arg), EXIT_FAILURE);
	arg->logger_mtx = malloc(sizeof(t_mutex) * 1);
	if (!arg->logger_mtx)
		return (safe_free(arg), EXIT_FAILURE);
	arg->meal_mtx = malloc(sizeof(t_mutex) * 1);
	if (!arg->meal_mtx)
		return (safe_free(arg), EXIT_FAILURE);
	arg->meal_num_mtx = malloc(sizeof(t_mutex) * 1);
	if (!arg->meal_num_mtx)
		return (safe_free(arg), EXIT_FAILURE);
	arg->sim_start = malloc(sizeof(t_mutex) * 1);
	if (!arg->sim_start)
		return (safe_free(arg), EXIT_FAILURE);
	if (pthread_mutex_init(arg->end_mtx, NULL) != 0)
		return (safe_free(arg), EXIT_FAILURE);
	if (pthread_mutex_init(arg->logger_mtx, NULL) != 0)
		return (safe_free(arg), EXIT_FAILURE);
	if (pthread_mutex_init(arg->meal_mtx, NULL) != 0)
		return (safe_free(arg), EXIT_FAILURE);
	if (pthread_mutex_init(arg->meal_num_mtx, NULL) != 0)
		return (safe_free(arg), EXIT_FAILURE);
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
	if (init_mtx(arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
