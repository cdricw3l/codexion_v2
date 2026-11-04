/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 07:39:28 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 14:39:27 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_heap.h"

/*

	heap parent node = (idx - 1) / 2
	heap children left = 2 * idx + 1
	heap children right = 2 * idx + 2


*/

/* heap max pop test*/
void unit_heap_min_pop(t_heap *heap)
{
	START_TEST;
	t_heap_node *n;
	
    write(STDOUT_FILENO,BBLU"\tExpected error msg --> "CRESET, ft_strlen(BBLU"\tExpected error msg -->"CRESET));
	assert(!heap_pop(heap, NULL));

	while (heap->heap_size)
	{
		n = heap_pop(heap, ft_cmp_min);
		/* is_heap_ok here check if the biggest value is the first node*/
		assert(is_heap_ok(heap, HEAP_TYPE_MIN));
		free(n->content);
		free(n);
	}
    assert(heap && heap->queue && heap->heap_size == 0);
	assert(!heap_pop(heap, ft_cmp_min));
	assert(!heap_pop(NULL, ft_cmp_min));
	END_TEST;
}

/* heap max push test*/
t_heap *unit_heap_min_push(void)
{
	START_TEST;
	size_t i;
	char *id;
	t_heap *heap;
	t_heap_node *node;

	heap = heap_init();
	assert(heap);
	assert(!heap->queue);
	assert(heap->heap_size == 0);
	
	i = 0;
	while (i <= 7)
	{
		id = ft_itoa((int)i);
		assert(id);
		node = heap_new_node(strdup(id));
		free(id);
		assert(heap_push(heap, node, ft_cmp_min));
		i++;
		assert(heap->heap_size == i);
	}
    
	id = ft_itoa(11);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_min));
	id = ft_itoa(10);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_min));
	id = ft_itoa(8);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_min));
	id = ft_itoa(9);
	node = heap_new_node(strdup(id));
	free(id);

	assert(heap_push(heap, node, ft_cmp_min));
	assert(heap_push(NULL, node, ft_cmp_min) == FALSE);
	assert(heap_push(heap, node, NULL) == FALSE);
	
	/* check if the array order is OK and if heap_get_node fonction is ok*/
	assert(atoi(heap_get_node(heap, 0)->content) == 0);
	assert(atoi(heap_get_node(heap, 1)->content) == 1);
	assert(atoi(heap_get_node(heap, 2)->content) == 2);
	assert(atoi(heap_get_node(heap, 3)->content) == 3);
	assert(atoi(heap_get_node(heap, 4)->content) == 4);
	assert(atoi(heap_get_node(heap, 5)->content) == 5);
	assert(atoi(heap_get_node(heap, 6)->content) == 6);
	assert(atoi(heap_get_node(heap, 7)->content) == 7);
	assert(atoi(heap_get_node(heap, 8)->content) == 11);
	assert(atoi(heap_get_node(heap, 9)->content) == 10);
	assert(atoi(heap_get_node(heap, 10)->content) == 8);
	assert(atoi(heap_get_node(heap, 11)->content) == 9);
	assert(heap_get_node(heap, 100) == NULL);
	assert(heap_get_node(NULL, 0) == NULL);
	
	
	END_TEST;
	return (heap);
}

void unit_heap_min(void)
{
	t_heap *heap;
    t_heap_node *node;

    heap = unit_heap_min_push();
    is_heap_ok(heap, HEAP_TYPE_MIN);
    unit_heap_min_pop(heap);
	
    heap_push(heap, heap_new_node(ft_itoa(1)), ft_cmp_min);
	assert(heap->heap_size == 1);
	node = heap_pop(heap, ft_cmp_min);
	assert(atoi(node->content) == 1);
	free(node->content);
	free(node);
	assert(heap->heap_size == 0);
	heap_push(heap, heap_new_node(ft_itoa(1)), ft_cmp_min);
	heap_push(heap, heap_new_node(ft_itoa(0)), ft_cmp_min);
	assert(heap->heap_size == 2);
	node = heap_pop(heap, ft_cmp_min);
	assert(atoi(node->content) == 0);
	free(node->content);
	free(node);
	node = heap_pop(heap, ft_cmp_min);
	assert(atoi(node->content) == 1);
	free(node->content);
	free(node);
	node = heap_pop(heap, ft_cmp_min);
	assert(node == NULL);


	
	heap_clear(&heap, clean_str_heap);
	assert(!heap);
}