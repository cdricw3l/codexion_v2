/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/04 07:45:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"



/*heap test unit*/
void unit_heap_new_node(void);
void unit_heap_init(void);
void unit_heap_max(void);

int unit_heap(void)
{
	START_BLOCK;

	unit_heap_init();
	unit_heap_new_node();
	unit_heap_max();
	return (TRUE);
}