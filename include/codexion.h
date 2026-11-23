/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 14:29:01 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/23 09:21:05 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>    // INT_MAX, INT_MIN, etc.
# include <errno.h>     // errno, ERANGE, EINVAL...
# include <stdio.h>     // printf, fprintf, FILE...
# include <string.h>    // strlen, strcmp, memcpy...
# include <unistd.h>    // read, write, close, fork... (POSIX)
# include <time.h>      //time
# include <assert.h>      
# include "color_codes.h"
# include "../src/heap/heap.h"
# include "../src/init/initialisation.h"

# define LEFT 0
# define RIGHT 1
# define TIMESTAMP_DONGLE 0
# define TIMESTAMP_COMPILATION 1
# define OFF 0
# define ON 1
# define END 1
# define CODER_MAX 200
# define PARAMS_SIZE 8
# define SCHEDULER_THREAD 0
# define MONITOR_THREAD 1
# define CODERS_THREAD_START 2

enum e_action
{
	TAKE,
	COMPILE,
	DEBUG,
	REFACTO,
	BURNED,
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
	arbitration
};

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
	int64_t		*last_compile;
	t_dongles		*dongle_l;
	t_dongles		*dongle_r;
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
void			destroy_request(t_request *request);

/****************************************** TIME MODULE */

int64_t		get_now(void);
/* peut etre pas utile time_diff*/
struct timespec	time_diff(struct timespec start, struct timespec end);
void			set_timestamp(t_coder *coder, int64_t now);
int64_t		get_timestamp(int64_t *timestamp,
					pthread_mutex_t *timestamp_mu);

/****************************************** DISPLAY MODULE */

void			display_action(t_coder *coder, int action);
void			display_params(int params[8]);

/****************************************** THREAD MANAGMENT MODULE */

int				launch_coders(t_sim *sim, t_coder *coders);
int				launch_scheduler(t_sim *sim, t_scheduler *scheduler);
int				launch_monitor(t_sim *sim, t_monitoring *monitoring);
void			joint_thread(t_sim *sim);

/****************************************** ROUTINE MODULE */

void			*scheduler_routine(void *data);
void			*monitoring_routine(void *data);
void			*coder_routine(void *data);
int				fifo(t_heap_node *n1, t_heap_node *n2);
int				edf(t_heap_node *n1, t_heap_node *n2);

/****************************************** PARSING MODULE */

int				parse_arguments(int argc, char **args, int params[8]);

/****************************************** ERROR MODULE */

void			*err_msg(char *err);
int				parsing_error_msg(int code, char *arg);

/****************************************** UTILS MODULE */

int				ft_is_digit(int c);
int				ft_memcopy(void *src, void *dst, unsigned long size);

int				get_dongle_id(int id, int number_of_coder, int type);
int				get_sim_state(int *state, pthread_mutex_t *state_mutex);
void			get_dongle_arr(size_t id, int params[8], int dongle[2]);
int				get_dongle_state(t_dongles *dongle);
bool			get_can_compile(t_coder *coder);

void			set_can_compile(t_coder *coder, bool value);
void			set_dongle_state(t_dongles *dongle, int state);
void			set_sim_state(int *stte, pthread_mutex_t *state_mu, int state);
#endif