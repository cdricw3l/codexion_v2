/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 14:29:01 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 15:11:26 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>    // INT_MAX, INT_MIN, etc.
# include <errno.h>     // errno, ERANGE, EINVAL...
# include <stdlib.h>    // malloc, free, exit, strtol...
# include <stdio.h>     // printf, fprintf, FILE...
# include <string.h>    // strlen, strcmp, memcpy...
# include <unistd.h>    // read, write, close, fork... (POSIX)
# include <time.h>      //time
# include <assert.h>      
# include "color_codes.h"
# include <pthread.h>
# include <stdbool.h>
# include "../src/heap/heap.h"

# define FALSE 0
# define TRUE 1
# define ERR 0
# define OK  1
# define FIFO 0
# define EDF 1
# define LEFT 0
# define RIGHT 1
# define TIMESTAMP_DONGLE 0
# define TIMESTAMP_COMPILATION 1
# define OFF 0
# define ON 1
# define CODER_MAX 200
# define PARAMS_SIZE 8

enum e_action
{
	TAKE,
	COMPILE,
	DEBUG,
	REFACTO,
	BURNED,
	END,
};

enum e_PARSING_ERROR
{
	NB_ARG,
	BAD_ARG
};

enum e_PARAMS
{
	number_of_coders,
	time_to_burnout,
	time_to_compile,
	time_to_debug,
	time_to_refactor,
	number_of_compiles_required,
	dongle_cooldown,
	scheduler
};

typedef struct s_heap			t_heap;
typedef struct s_heap_node		t_heap_node;
typedef struct s_request_queue	t_request_queue;
typedef struct s_request		t_request;
typedef struct s_coder			t_coder;

typedef struct s_monitoring
{
	int				params[8];
	int				*simulation_state;
	pthread_mutex_t	*simulation_state_mu;
	clock_t			*timestamp;
	pthread_mutex_t	*timestamp_mu;
	t_coder			*coders;

}	t_monitoring;

typedef struct s_scheduler
{
	int				params[8];
	t_request_queue	*queue;
	t_heap			**heaps;
	pthread_t		scheduler_thread;
	int				*simulation_state;
	pthread_mutex_t	*simulation_state_mu;

}	t_scheduler;

typedef struct s_dongles
{
	size_t			id;
	time_t			last_use;
	pthread_mutex_t	*dongle;

}	t_dongles;

struct s_coder
{
	int				params[8];
	clock_t			simulation_start;
	int				*simulation_state;
	pthread_mutex_t	*simulation_state_mu;
	size_t			coder_id;
	bool			*can_compile;
	pthread_mutex_t	*can_compile_mu;
	pthread_cond_t	*can_compile_cond;
	t_request_queue	*queue;
	t_dongles		*dongle_left;
	t_dongles		*dongle_right;
	clock_t			*timestamp;
	pthread_mutex_t	*timestamp_mu;
	pthread_mutex_t	*display_mu;

};

typedef struct s_sim
{
	int				params[8];
	pthread_t		*thread;
	int				simulation_state;
	pthread_mutex_t	*simulation_state_mu;
	bool			*can_compile;
	pthread_mutex_t	*can_compile_mu;
	pthread_cond_t	*can_compile_cond;
	clock_t			*timestamp;
	pthread_mutex_t	*timestamp_mu;
	t_request_queue	*queue;
	pthread_mutex_t	*request_queue_mu;
	pthread_mutex_t	*display_mu;
	pthread_mutex_t	*dongle_mu;

}	t_sim;

/****************************************** INITIALISATION MODULE */

t_sim			*sim_init(int params[8]);
t_dongles		*dongle_init(int params[8], t_sim *sim);
t_coder			*coders_init(int params[8], t_sim *sim, t_dongles *dongle);
t_scheduler		*scheduler_init(int params[8], t_sim *sim);
t_monitoring	*monitoring_init(int params[8], t_sim *sim, t_coder *coders);
void			*sim_clean(t_sim **s);
void			*scheduler_clean(t_scheduler **s);
void			*clean_dynamique_mutex(pthread_mutex_t **mutex, int nb);
void			*clean_dynamique_cond(pthread_cond_t **cond, int nb);
pthread_t		*threads_init(int nb);
pthread_mutex_t	*init_dynamique_mutex(int nb);
pthread_cond_t	*init_dynamique_cond(int nb);
bool			*can_compile_init(int nb);
time_t			*timestamp_init(int nb);

/****************************************** REQUEST MODULE */

struct s_request_queue
{
	t_request		**queue;
	size_t			queue_size;
	size_t			request_counter;
	pthread_mutex_t	queue_mutex;

} ;

struct s_request
{
	size_t			request_id;
	size_t			coder_id;
	bool			*can_compile;
	pthread_cond_t	*can_compile_cond;
	pthread_mutex_t	*can_compile_mu;
	clock_t			*last_compile;
	void			*next;

} ;

t_request_queue	*request_queue_init(void);
int				request_push(t_coder *coder);
t_request		*request_pop(t_request_queue *queue);
t_request		*request_get_last_node(t_request *current);
int				request_destroy_queue(t_request_queue **q);
void			request_clear_queue(t_request_queue *queue);
size_t			request_get_queue_size(t_request_queue *queue);
void			request_display_queue(t_request_queue *queue);
void			request_display_node(t_request *request);

/****************************************** TIME MODULE */

clock_t			get_now(void);
/* peut etre pas utile time_diff*/
struct timespec	time_diff(struct timespec start, struct timespec end);
void			set_timestamp(t_coder *coder);
clock_t			get_timestamp(clock_t *timestamp,
					pthread_mutex_t *timestamp_mu);

/****************************************** DISPLAY MODULE */

void			display_action(t_coder *coder, int action);
void			display_params(int params[8], int nb);

/****************************************** THREAD MANAGMENT MODULE */

int				launch_coders(t_sim *sim, t_coder *coders,
					void *(*routine)(void *), clock_t start);
int				joint_coders(t_sim *sim);

/****************************************** ROUTINE MODULE */

void			*scheduler_routine(void *data);
void			*monitoring_routine(void *data);
void			*coder_routine(void *data);
int				fifo(t_heap_node *n1, t_heap_node *n2);

/****************************************** PARSING MODULE */

int				parse_arguments(char **args, int params[8]);

/****************************************** ERROR MODULE */

void			*err_msg(char *err);
int				parsing_error_msg(int code, char *arg);

/****************************************** UTILS MODULE */

size_t			get_str_arr_len(char **str_arr);
int				ft_is_digit(int c);
int				ft_memcopy(void *src, void *dst, unsigned long size);
int				get_dongle_id(int id, int number_of_coder, int type);
int				get_sim_state(int *state, pthread_mutex_t *state_mutex);
void			set_sim_state(int *state, pthread_mutex_t *state_mutex,
					int new_state);
void			get_dongle_arr(size_t id, int params[8], int dongle[2]);

#endif