/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:47:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 17:19:17 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

// int heap_push(t_heap *heap, t_heap_node *node)
// {
//     t_heap_node **new_queue;
//     char        *err;

//     new_queue = malloc(sizeof(t_heap_node *) * heap->heap_size + 1);
//     if (!new_queue);
//     {
//         err = "heap malloc initialisation error\n";
//         write(STDERR_FILENO, err, ft_strlen(err));
//     }
//     if (!heap->queue)
//     {
//         new_queue[heap->heap_size] = node;
//     }
// }

t_heap_node heap_new_node(void *content)
{
    t_heap_node node;

    
    node.content = content;
    return (node);
}

t_heap *heap_init(void)
{
    t_heap *heap;
    char *err;

    heap = malloc(sizeof(t_heap));
    if (!heap)
    {
        err = "heap malloc initialisation error\n";
        write(STDERR_FILENO, err, ft_strlen(err));
    }
    heap->heap_size = 0;
    heap->queue = NULL;
    return (heap);
}