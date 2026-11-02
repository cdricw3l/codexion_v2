/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:47:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 12:59:15 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

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