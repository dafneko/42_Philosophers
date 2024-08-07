/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:58:39 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/08 00:11:29 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define INT_MAX 2147483647
#define INT_MAX_LEN 9
#define ERROR -1

#define ALIVE 0
#define DEAD 1
#define THINK 2
#define EAT 3
#define SLEEP 4

typedef long long		t_ll;
typedef pthread_mutex_t	t_mutex;

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

// typedef struct s_fork
// {
// 	t_mutex mutex;

// };

typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					left_meals;
	t_ll				eat_micro;
	t_ll				sleep_micro;
	t_mutex				*logger_mtx;
	t_mutex				*end_mtx;
	t_mutex				*meal_mtx;
	t_mutex				*meal_num_mtx;
	int					*sig;
}						t_data;

typedef struct s_philo
{
	t_ll				start_time;
	t_ll				last_meal_time;
	t_mutex				*right_fork;
	t_mutex				*left_fork;
	t_data				arg;
	int					id;
	int					*end_sig;
}						t_philo;

/* parse */
int						parse_arguments(char *str, int *ms);
int						init_data(int ac, char **argv, t_data *arg);
int						free_all(t_philo *philo, pthread_t *philo_th);
int						start_lifetime(t_data *args);
int						thus_god_created_man(t_data *args, t_philo all_philos[],
							pthread_t *philo_th);
t_ll					look_at_clock(void);
t_bool					is_end(t_philo *philo);
void					life_updates(t_philo *philo, int status);
void					*daily_routine(void *ptr);
int						free_all(t_philo *philo, pthread_t *philo_th);
int						grim_reaper(t_philo *all_philos);