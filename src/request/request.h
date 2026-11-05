/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:28:55 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 14:59:36 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
#define REQUEST_H

#include <stdlib.h>    // malloc, free, exit, strtol...
#include <stdio.h>     // printf, fprintf, FILE...
#include <string.h>    // strlen, strcmp, memcpy...
#include <unistd.h>    // read, write, close, fork... (POSIX)
#include "../../include/codexion.h"

typedef struct s_request
{
	size_t          request_id;
	size_t          coder_id;
    bool            *can_compile;
    pthread_cond_t  *can_compile_cond;
    pthread_mutex_t *can_compile_mu;
    void            *next;

} t_request;

typedef struct s_request_queue
{
    t_request **queue;
    size_t queue_size;
    pthread_mutex_t queue_mutex;
    
} t_request_queue;

t_request_queue *request_queue_init(void);
t_request *request_new_node(t_coder *coder, t_request_queue *queue);
#endif