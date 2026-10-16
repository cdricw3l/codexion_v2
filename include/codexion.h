/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 18:09:57 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/16 08:13:31 by cdric.b          ###   ########.fr       */
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
#include "color-codes.h"
#include <pthread.h>

#define FALSE 0
#define TRUE 1
#define ERR -1
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

typedef struct s_requests
{
    size_t              request_id;
    size_t              coder_id;
    clock_t             coder_last_compilation;
    struct s_requests   *left;
    struct s_requests   *right;

} t_requests;

typedef struct s_dongle
{
    pthread_mutex_t dongle;
    clock_t         last_use;
    int             request_queue_size;
    t_requests      **requests_queue;

} t_dongle;




/*
    data arr:
        - clock_t   timestamp
        - t_dongle  dongles
    mutext arr:
        - mutext dongles
        - mutext timestamps
    mutext unique:
        - display mutex
        - simulation mutex
    cond arr
        - cond dongle
*/

/* display */
void            display_params(int params[8], int nb);

/* parsing */
int             parse_arguments(char **args, int params[8]);

/* error */
int             msg_error(int code);
int             parsing_error_msg(int code, char *arg);
void            ft_putnbr_error(int fd, int nb, int base);

/* utils */

int             ft_is_digit(char c);
size_t          get_str_arr_len(char **str_arr);

/* thread utils */

pthread_mutex_t	*init_dynamique_mutex(int nb);
pthread_cond_t	*init_dynamique_cond(int nb);
int             clean_dynamique_mutex(pthread_mutex_t **mutex, int nb);
int             clean_dynamique_cond(pthread_cond_t **cond, int nb);

#endif