/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 00:19:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/21 00:20:20 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
