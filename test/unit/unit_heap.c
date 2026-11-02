/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/02 18:26:10 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

/*

	heap parent node = (idx - 1) / 2
	heap children left = 2 * idx + 1
	heap children right = 2 * idx + 2


*/

int ft_cmp(t_heap_node parent, t_heap_node current)
{
	char *s_parent;
	char *s_current;

	s_parent = (char *)parent.content;
	s_current = (char *)current.content;
	printf("Parent content: %s\n", s_parent);
	printf("Current content: %s\n", s_current);
	if (strcmp(s_parent, s_current) < 0)
		return (TRUE);
	return (FALSE);
}

void 	heap_swap_node(t_heap_node *parent, t_heap_node *current)
{
	printf("Swap nedded\n");

	void *tmp;

	tmp = parent->content;
	parent->content = current->content;
	current->content = tmp;
}

int heap_push(t_heap *heap, t_heap_node node, int (*cmp)(t_heap_node parent, t_heap_node current))
{
	t_heap_node *new_queue;
	size_t 		idx_current;
	size_t 		idx_parent;
	char		*err;

	if (!heap)
		return (FALSE);
	new_queue = malloc(sizeof(t_heap_node) * (heap->heap_size + 1));
	if (!new_queue)
	{
		err = "heap queue malloc initialisation error\n";
        write(STDERR_FILENO, err, ft_strlen(err));
	}
	if (ft_memcopy(heap->queue, new_queue, sizeof(t_heap_node) * heap->heap_size) == ERR)
	{
		err = "memcpy heap->queue error\n";
		return (FALSE);
	}
	if (heap->queue)	
		free(heap->queue);
	new_queue[heap->heap_size] = node;
	heap->queue = new_queue;
	heap->heap_size++;
	(void)cmp;
	if (heap->heap_size < 2)
		return (TRUE);
	idx_current = heap->heap_size - 1;
	idx_parent = ((idx_current) - 1) / 2;

	while (idx_parent >= 0 && cmp(heap->queue[idx_parent], heap->queue[idx_current]))
	{
		heap_swap_node(&heap->queue[idx_parent], &heap->queue[idx_current]);
		idx_current = idx_parent;
		idx_parent = ((idx_current) - 1) / 2;
	}
	
	return (TRUE);
}

void unit_heap_push(void)
{
	START_TEST;
	size_t i;
	char *id;
	t_heap *heap;
	t_heap_node node;

	heap = heap_init();
	assert(heap);
	assert(!heap->queue);
	assert(heap->heap_size == 0);
	
	i = 0;
	while (i < 100)
	{
		id = ft_itoa((int)i);
		assert(id);
		node = heap_new_node(id);
		assert(heap_push(heap, node, ft_cmp));
		i++;
		assert(heap->heap_size == i);
	}
	assert(heap->heap_size == 100);
	i = 0;
	while (i < heap->heap_size)
	{
		printf("Node %zu: %s\n", i, (char *)heap->queue[i].content);
		i++;
	}
	
	END_TEST;
}

void unit_heap_new_node(void)
{
	START_TEST;
	t_heap_node node;
	
	node = heap_new_node(NULL);
	assert(node.content == NULL);

	node = heap_new_node(strdup("hello world"));
	assert(strcmp((char *)node.content, "hello world") == 0);
	free(node.content);
	END_TEST;
}

void unit_heap_init(void)
{
	START_TEST;

	t_heap *heap;

	heap = heap_init();
	assert(heap);
	assert(heap->heap_size == 0);
	assert(!heap->queue);
	free(heap->queue);
	free(heap);
	END_TEST;	
}


int unit_heap(void)
{
	START_BLOCK;

	unit_heap_init();
	unit_heap_new_node();
	
	unit_heap_push();
	return (TRUE);
}