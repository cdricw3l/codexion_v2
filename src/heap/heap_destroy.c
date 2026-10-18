/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 10:06:08 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/18 10:12:54 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

void	heap_destroy(t_heap **heap)
{
	heap_clear((*heap)->queue, free);
	free((*heap)->queue);
	(*heap)->queue = NULL;
	free(*heap);
	*heap = NULL;
}
