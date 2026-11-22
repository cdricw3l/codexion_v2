/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 21:20:23 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:47:04 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALISATION_H
# define INITIALISATION_H

# include <pthread.h>
# include <stdint.h>
# include <stdlib.h> 
# include <stdbool.h> 
# include <string.h>

# define ERR 0
# define OK  1
# define FIFO 0
# define EDF 1

typedef struct s_heap			t_heap;
typedef struct s_heap_node		t_heap_node;
typedef struct s_request_queue	t_request_queue;
typedef struct s_request		t_request;
typedef struct s_coder			t_coder;


typedef struct s_monitoring
{
	int				params[8];
	int				*simulation_state;
	pthread_mutex_t	*state_mu;
	uint64_t		*timestamp;
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
	pthread_mutex_t	*state_mu;
	int (*f) (t_heap_node *, t_heap_node *);

}	t_scheduler;

typedef struct s_dongles
{
	size_t			id;
	size_t			is_used;
	time_t			last_use;
	pthread_mutex_t	*dongle;
	pthread_mutex_t	is_used_mu;

}	t_dongles;

struct s_coder
{
	int				params[8];
	int				counter;
	uint64_t		simulation_start;
	int				*simulation_state;
	pthread_mutex_t	*state_mu;
	size_t			coder_id;
	bool			*can_compile;
	pthread_mutex_t	*can_compile_mu;
	pthread_cond_t	*can_compile_cond;
	t_request_queue	*queue;
	t_dongles		*dongle_left;
	t_dongles		*dongle_right;
	uint64_t		*timestamp;
	pthread_mutex_t	*timestamp_mu;
	pthread_mutex_t	*display_mu;

};

typedef struct s_sim
{
	int				params[8];
	pthread_t		*thread;
	int				simulation_state;
	t_request_queue	*queue;
	bool			*can_compile;
	uint64_t		*timestamp;
	pthread_cond_t	*can_compile_cond;
	pthread_mutex_t	*dongle_mu;
	pthread_mutex_t	*display_mu;
	pthread_mutex_t	*timestamp_mu;
	pthread_mutex_t	*can_compile_mu;
	pthread_mutex_t	*request_queue_mu;
	pthread_mutex_t	*state_mu;

}	t_sim;

typedef struct s_data
{
	t_sim			*sim;
	t_dongles		*dongles;
	t_coder			*coder;
	t_scheduler		*scheduler;
	t_monitoring	*monitoring;

}	t_data;

int				initialisation(t_data *d, int params[8]);
int				clear_data(t_data *d, int code);
t_sim			*sim_init(int params[8]);
t_dongles		*dongle_init(t_sim *sim, int params[8]);
t_coder			*coders_init(t_sim *sim, t_dongles *dgl, int p[8]);
t_scheduler		*scheduler_init(t_sim *sim, int params[8]);
t_monitoring	*monitoring_init(t_sim *sim, t_coder *coders, int params[8]);
void			*clean_sim(t_sim **s);
void			*clean_scheduler(t_scheduler **s);
// void			*clean_dynamique_mutex(pthread_mutex_t **mutex, int nb);
// void			*clean_dynamique_cond(pthread_cond_t **cond, int nb);
pthread_t		*threads_init(int nb);
pthread_mutex_t	*init_dynamique_mutex(int nb);
pthread_cond_t	*init_dynamique_cond(int nb);
bool			*can_compile_init(int nb);
time_t			*timestamp_init(int nb);

#endif