/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 18:24:47 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/23 19:01:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"

static void	clear_queue(t_heap_node *root, void (*f)(void *))
{
	if (!root)
		return ;
	clear_queue(root->left, f);
	clear_queue(root->right, f);
	f(root->content);
	f(root);
}

void	heap_clear(t_heap *heap, void (*f)(void *))
{
	t_heap_node **queue;

	if (!heap || !heap->queue || !*heap->queue)
		return ;
	queue = heap->queue;
	clear_queue(*queue, f);
	*queue = NULL;
	heap->size_queue = 0;
}
