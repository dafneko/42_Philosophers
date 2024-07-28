#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647
#define INT_MAX_LEN 9
#define ERROR -1


typedef long long t_ll;
typedef pthread_mutex_t t_mutex;


typedef enum e_bool {
	FALSE,
	TRUE
} 	t_bool;


// typedef struct s_fork
// {
// 	t_mutex mutex;

// };


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
    t_ll start_time;       // 8 bytes
    t_ll last_meal_ms;     // 8 bytes
    t_mutex *right_fork;   // 8 bytes on 64-bit systems
    t_mutex *left_fork;    // 8 bytes on 64-bit systems
    t_args arg;            // 20 bytes
    t_mutex logger;        // Size depends on the system (assuming 40 bytes)
    t_mutex end;           // Size depends on the system (assuming 40 bytes)
    int id;                // 4 bytes
    int left_meals;        // 4 bytes
    t_bool end_sig;        // 4 bytes (since it's an enum)
} t_philo;

/* parse */
int parse_params(char *str, int *ms);