#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define INT_MAX 2147483647
#define INT_MAX_LEN 9
#define ERROR -1

#define ALIVE 0
#define DEAD 1
#define THINK 2
#define EAT 3
#define SLEEP 4

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

 
typedef struct s_data
{
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int left_meals;
	t_ll eat_micro;
	t_ll sleep_micro;
	t_mutex *logger_mtx;
	t_mutex *end_mtx;
	t_mutex *meal_mtx;
	int *sig;
} t_data;

typedef struct s_philo
{
    t_ll start_time;       // 8 bytes
    t_ll last_meal_time;     // 8 bytes
    t_mutex *right_fork;   // 8 bytes on 64-bit systems
    t_mutex *left_fork;    // 8 bytes on 64-bit systems
    t_data arg;            // 20 bytes
    int id;                // 4 bytes
    int *end_sig;        // 4 bytes (since it's an enum)
    // int left_meals;        // 4 bytes
} t_philo;

/* parse */
int parse_arguments(char *str, int *ms);
int init_data(int ac, char **argv, t_data *arg);
int start_lifetime(t_data *args);
t_ll look_at_clock(void);
t_bool is_end(t_philo *philo);
void life_updates(t_philo *philo, int status);
void *daily_routine(void *ptr);
int free_all(t_philo *philo);
int grim_reaper(t_philo *all_philos);