/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 05:27:38 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 05:21:17 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *init_coder(int nb, t_request_queue *queue)
{
    t_coder *coders;
    int i;

    coders = malloc(sizeof(t_coder) * nb);
    assert(coders);
    i = 0;
    while (i < nb)
    {
        coders[i].can_compile = can_compile_init(1);
        coders[i].can_compile_cond = init_dynamique_cond(1);
        coders[i].can_compile_mu = init_dynamique_mutex(1);
        pthread_cond_init(coders[i].can_compile_cond, NULL);
        pthread_mutex_init(coders[i].can_compile_mu, NULL);
        coders[i].coder_id = i;
        coders[i].queue = queue;
        i++;
    }
    return (coders);
}

int check_queue_unique_request(t_request *root)
{

    t_request *next;

    while (root)
    {
        next = root->next;
        while (next)
        {
            if (root->request_id == next->request_id)
            {
                printf("Root:\n");
                request_display_node(root);
                printf("Next:\n");
                request_display_node(next);
                return (false);
            }
            next = next->next;
        }
        root = root->next;
    }
    return (true);
}

void *push_request_routine(void *data)
{
    size_t i;
    t_coder *coder;

    coder = (t_coder *)data;
    i = 0;
    assert(coder->queue);
    while (i < 10)
    {
        assert(request_push(coder));
        i++;
    }
    return (NULL);
}