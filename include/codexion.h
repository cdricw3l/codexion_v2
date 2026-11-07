/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 18:09:57 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/07 16:23:43 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CODEXION_H
#define CODEXION_H


#include <limits.h>    // INT_MAX, INT_MIN, etc.
#include <errno.h>     // errno, ERANGE, EINVAL...
#include <stdlib.h>    // malloc, free, exit, strtol...
#include <stdio.h>     // printf, fprintf, FILE...
#include <string.h>    // strlen, strcmp, memcpy...
#include <unistd.h>    // read, write, close, fork... (POSIX)
#include <time.h>      //time
#include <assert.h>      
#include "color-codes.h"
#include <pthread.h>
#include <stdbool.h>


#define FALSE 0
#define TRUE 1
#define ERR 0
#define OK  1
#define FIFO 0
#define EDF 1
#define LEFT 0
#define RIGHT 1
#define TIMESTAMP_DONGLE 0
#define TIMESTAMP_COMPILATION 1
#define OFF 0
#define ON 1
#define CODER_MAX 200
#define PARAMS_SIZE 8
#define NL printf("\n")

enum e_error_init
{
    CODER,
    STATE,
    STATE_MUTEX,
    TIMESTAMPS,
    TIMESTAMPS_MUTEX,
    CODER_MUTEX,
    CODER_COND,
    COUNTER,
    COUNTER_MU
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

typedef struct s_request_queue t_request_queue;
typedef struct s_request t_request;


typedef struct s_dongles
{
    size_t id;
    time_t          last_use;
    pthread_mutex_t *dongle;
    
} t_dongles;


typedef struct s_coder
{
    size_t          coder_id;
    bool            *can_compile;
    pthread_mutex_t *can_compile_mu;
    pthread_cond_t  *can_compile_cond;
    t_request_queue *queue;
    t_dongles       *dongle_left;
    t_dongles       *dongle_right;
    int             params[8];

} t_coder;

typedef struct s_sim
{
    bool            *can_compile;
    pthread_t       *thread;
    pthread_mutex_t *display_mu;
    pthread_mutex_t *request_queue_mu;
    pthread_mutex_t *timestamp_mu;
    pthread_mutex_t *can_compile_mu;
    pthread_mutex_t *dongle_mu;
    pthread_cond_t  *can_compile_cond;
    time_t          *timestamp;
    t_request_queue *queue;
    int             params[8];

} t_sim;

/****************************************** INITIALISATION MODULE ***********************************/

t_sim           *sim_init(int params[8]);
t_dongles       *dongle_init(int nb, t_sim *sim);
t_coder         *coders_init(int params[8], t_sim *sim, t_dongles *dongle);

void            *clean_dynamique_mutex(pthread_mutex_t **mutex, int nb);
void            *clean_dynamique_cond(pthread_cond_t **cond, int nb);
void            *clean_sim(t_sim **s);


/****************************************** REQUEST MODULE ******************************************/

struct s_request_queue
{
	t_request **queue;
	size_t queue_size;
	size_t request_counter;
	pthread_mutex_t queue_mutex;
	
} ;

struct s_request
{
	size_t          request_id;
	size_t          coder_id;
	bool            *can_compile;
	pthread_cond_t  *can_compile_cond;
	pthread_mutex_t *can_compile_mu;
	void            *next;

} ;

t_request_queue *request_queue_init(void);
t_request       *request_new_node(t_coder *coder);
int				request_push(t_request_queue *queue, t_request *request);
t_request	    *request_pop(t_request_queue *queue);
t_request		*request_get_last_node(t_request *current);
int 			request_destroy_queue(t_request_queue **q);
void            request_clear_queue(t_request_queue *queue);
size_t			request_get_queue_size(t_request_queue *queue);
void            request_display_queue(t_request_queue *queue);
void            request_display_node(t_request *request);

/****************************************************************************************************/

/****************************************** HEAP MODULE *********************************************/

typedef struct s_heap_node
{
	void				*content;

}	t_heap_node;

typedef struct s_heap
{
	t_heap_node	**queue;
	size_t		heap_size;		

}	t_heap;

t_heap		*heap_init(void);
t_heap_node	*heap_new_node(void *content);
void		heap_swap_node(t_heap_node *parent, t_heap_node *current);
void		heap_clear(t_heap **heap, void (*del)(void *));
int			heap_push(t_heap *heap, t_heap_node *node,
				int (*cmp)(t_heap_node *, t_heap_node *));
t_heap_node	*heap_pop(t_heap *heap, int (*cmp)(t_heap_node *, t_heap_node *));
t_heap_node	*heap_get_node(t_heap *heap, size_t idx);

/****************************************************************************************************/





/* display */
void            display_params(int params[8], int nb);

/* parsing */
int             parse_arguments(char **args, int params[8]);

/* Errror */

void            *err_msg(char *err);
int	            parsing_error_msg(int code, char *arg);

/* utils */

size_t  get_str_arr_len(char **str_arr);
size_t  ft_strlen(char *str);
int     ft_is_digit(int c);
int     ft_memcopy(void *src, void *dst, unsigned long size);
int     get_dongle(int id, int number_of_coder, int type);
#endif