/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/02 21:21:53 by cebouhad         ###   ########.fr       */
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
	int parent_value;
	int current_value;

	s_parent = (char *)parent.content;
	s_current = (char *)current.content;

	parent_value = atoi(s_parent);
	current_value = atoi(s_current);
	printf("Parent content: %s\n", s_parent);
	printf("Current content: %s\n", s_current);
	if (parent_value < current_value)
		return (TRUE);
	return (FALSE);
}

void clean_str_heap(void *content)
{
	char *str;

	str = (char *)content;
	free(str);
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
	while (i < 7)
	{
		id = ft_itoa((int)i);
		assert(id);
		node = heap_new_node(id);
		assert(heap_push(heap, node, ft_cmp));
		i++;
		assert(heap->heap_size == i);
	}

	id = ft_itoa(11);
	node = heap_new_node(id);
	assert(heap_push(heap, node, ft_cmp));
	id = ft_itoa(10);
	node = heap_new_node(id);
	assert(heap_push(heap, node, ft_cmp));
	id = ft_itoa(8);
	node = heap_new_node(id);
	assert(heap_push(heap, node, ft_cmp));
	id = ft_itoa(9);
	node = heap_new_node(id);
	assert(heap_push(heap, node, ft_cmp));
	assert(heap_push(NULL, node, ft_cmp) == FALSE);
	assert(heap_push(heap, node, NULL) == FALSE);
	assert(atoi(heap->queue[0].content) == 11);
	assert(atoi(heap->queue[1].content) == 10);
	assert(atoi(heap->queue[2].content) == 5);
	assert(atoi(heap->queue[3].content) == 6);
	assert(atoi(heap->queue[4].content) == 9);
	assert(atoi(heap->queue[5].content) == 1);
	assert(atoi(heap->queue[6].content) == 4);
	assert(atoi(heap->queue[7].content) == 0);
	assert(atoi(heap->queue[8].content) == 3);
	assert(atoi(heap->queue[9].content) == 2);
	assert(atoi(heap->queue[10].content) == 8);

	heap_clear(&heap, clean_str_heap);
	assert(!heap);
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