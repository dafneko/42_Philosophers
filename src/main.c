/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:34 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/09 00:22:47 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
arguments: ./philo num_of_philos time_to_die time_to_eat
time_to_sleep  num_of_meals (optional)
*/
int	main(int ac, char **argv)
{
	t_data	arg;

	if (init_data(ac, argv, &arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_lifetime(&arg);
	return (EXIT_SUCCESS);
}
