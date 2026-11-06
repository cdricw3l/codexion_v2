/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 05:27:38 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 05:28:05 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *get_coder(size_t id, t_request_queue *queue)
{
    t_coder *coder;

    coder = malloc(sizeof(t_coder));
    assert(coder);
    coder->can_compile = false;
    pthread_cond_init(&coder->can_compile_cond,NULL);
    pthread_mutex_init(&coder->can_compile_mu, NULL);
    coder->coder_id = id;
    coder->queue = queue;
    return (coder);
}
