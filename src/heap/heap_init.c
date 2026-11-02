/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:47:41 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 12:50:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

t_heap heap_init(void)
{
    t_heap *heap;

    heap = malloc(sizeof(t_heap))
    if (!heap)
    {
        write(STDERR_FILENO, "heap malloc initialisation error\n")
    }
}