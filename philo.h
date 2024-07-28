#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647
#define INT_MAX_LEN 9
#define ERROR -1
typedef long long t_ll;

typedef enum e_bool {
	FALSE,
	TRUE
} 	t_bool;


typedef struct s_arguments
{
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_meals;
} t_args;

typedef struct s_philo
{
	t_bool death;
	t_bool end;
	t_ll last_meal_ms;
}	t_philo;


/* parse */
int parse_params(char *str, int *ms);