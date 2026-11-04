/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:10:49 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/03 04:59:55 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_clear(t_heap **heap, void (*del)(void *content))
{
	size_t	i;
	t_heap	*h;

	h = *heap;
	i = 0;
	while (i < h->heap_size)
	{
		del(h->queue[i]);
		i++;
	}
	free(h->queue);
	free(*heap);
	*heap = NULL;
}
