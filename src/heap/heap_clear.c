/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:10:49 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 21:15:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_clear(t_heap **heap, void (*del)(void *content))
{
	size_t	i;

	while (i < (*heap)->heap_size)
	{
		del((*heap)->queue[i].content);
		i++;
	}
	free(*heap);
	*heap = NULL;
}
