/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:10:49 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 21:24:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	heap_clear(t_heap **heap, void (*del)(void *content))
{
	size_t	i;
	t_heap	*h;

	if (!*heap)
		return ;
	h = *heap;
	i = 0;
	while (i < h->heap_size)
	{
		del(h->queue[i]);
		i++;
	}
	if (h->queue)
		free(h->queue);
	free(*heap);
	*heap = NULL;
}
