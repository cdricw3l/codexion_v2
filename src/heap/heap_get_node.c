/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_get_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 04:32:04 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 21:24:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_heap_node	*heap_get_node(t_heap *heap, size_t idx)
{
	if (!heap
		|| !heap->queue
		|| idx > heap->heap_size - 1
		|| heap->heap_size <= 0)
		return (NULL);
	return (heap->queue[idx]);
}
