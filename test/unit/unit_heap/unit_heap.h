/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 13:57:13 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/04 14:32:53 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_HEAP_H
#define UNIT_HEAP_H

#define HEAP_TYPE_MIN   0
#define HEAP_TYPE_MAX   1

#include "../unit.h"

void    unit_heap_new_node(void);
void    unit_heap_init(void);
void    unit_heap_max(void);
void    unit_heap_min(void);

/* utils fonction */
int     is_heap_ok(t_heap *heap, int type);
void    clean_str_heap(void *ptr);
int     ft_cmp_max(t_heap_node *parent, t_heap_node *current);
int     ft_cmp_min(t_heap_node *parent, t_heap_node *current);
void    display_heap(t_heap *heap);

#endif