/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 07:39:28 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 07:46:45 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

/*

	heap parent node = (idx - 1) / 2
	heap children left = 2 * idx + 1
	heap children right = 2 * idx + 2


*/

void clean_str_heap(void *ptr);
int ft_cmp_max(t_heap_node *parent, t_heap_node *current);

/* heap max pop test*/
void unit_heap_max_pop(void)
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
	while (i < 7)
	{
		id = ft_itoa((int)i);
		assert(id);
		node = heap_new_node(strdup(id));
		free(id);
		assert(heap_push(heap, node, ft_cmp_max));
		i++;
		assert(heap->heap_size == i);
	}

	id = ft_itoa(11);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(10);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(8);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(9);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(7);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));

	t_heap_node *n;
	size_t j;

	j = heap->heap_size - 1;
	while (heap->heap_size)
	{
		n = heap_pop(heap, ft_cmp_max);
		assert((size_t)atoi(n->content) == j);
		j--;
		free(n->content);
		free(n);
	}
	assert(!heap_pop(heap, ft_cmp_max));
	/* clear fonction. Check with valgrind*/
	heap_clear(&heap, clean_str_heap);
	assert(!heap);
	END_TEST;
}

/* heap max push test*/
void unit_heap_max_push(void)
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
	while (i < 7)
	{
		id = ft_itoa((int)i);
		assert(id);
		node = heap_new_node(strdup(id));
		free(id);
		assert(heap_push(heap, node, ft_cmp_max));
		i++;
		assert(heap->heap_size == i);
	}

	id = ft_itoa(11);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(10);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(8);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	id = ft_itoa(9);
	node = heap_new_node(strdup(id));
	free(id);
	assert(heap_push(heap, node, ft_cmp_max));
	assert(heap_push(NULL, node, ft_cmp_max) == FALSE);
	assert(heap_push(heap, node, NULL) == FALSE);
	
	/* check if the array order is OK and if heap_get_node fonction is ok*/
	assert(atoi(heap_get_node(heap, 0)->content) == 11);
	assert(atoi(heap_get_node(heap, 1)->content) == 10);
	assert(atoi(heap_get_node(heap, 2)->content) == 5);
	assert(atoi(heap_get_node(heap, 3)->content) == 6);
	assert(atoi(heap_get_node(heap, 4)->content) == 9);
	assert(atoi(heap_get_node(heap, 5)->content) == 1);
	assert(atoi(heap_get_node(heap, 6)->content) == 4);
	assert(atoi(heap_get_node(heap, 7)->content) == 0);
	assert(atoi(heap_get_node(heap, 8)->content) == 3);
	assert(atoi(heap_get_node(heap, 9)->content) == 2);
	assert(atoi(heap_get_node(heap, 10)->content) == 8);
	assert(heap_get_node(heap, 100) == NULL);
	assert(heap_get_node(NULL, 0) == NULL);
	
	/* clear fonction. Check with valgrind*/
	heap_clear(&heap, clean_str_heap);
	assert(!heap);
	END_TEST;
}


void unit_heap_max(void)
{
    unit_heap_max_push();
    unit_heap_max_pop();
}