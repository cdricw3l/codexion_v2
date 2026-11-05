/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 18:09:57 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/05 14:53:33 by cebouhad         ###   ########.fr       */
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

#include "../src/heap/heap.h"

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




typedef struct s_sim
{
    int type_queue;

    bool            *can_compile;
    pthread_mutex_t display_mu;
    pthread_mutex_t request_queue_mu;
    pthread_mutex_t *timestamp_mu;
    pthread_mutex_t *can_compile_mu;
    pthread_cond_t  *can_compile_cond;
    time_t          *timestamp;

} t_sim;


typedef struct t_coder
{
    size_t          coder_id;
    bool            *can_compile;
    pthread_mutex_t *can_compile_mu;
    pthread_cond_t  *can_compile_cond;

} t_coder;



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
#endif