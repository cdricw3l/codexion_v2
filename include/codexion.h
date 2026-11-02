/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 18:09:57 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/02 13:04:50 by cebouhad         ###   ########.fr       */
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


/* display */
void            display_params(int params[8], int nb);

/* parsing */
int             parse_arguments(char **args, int params[8]);

/* Errror */

int	            parsing_error_msg(int code, char *arg);

/* utils */

int             ft_is_digit(char c);
size_t	        ft_strlen(char *str);

#endif