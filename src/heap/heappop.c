/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heappop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 08:10:48 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/23 15:24:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "../../include/codexion.h"

void display_r(void *ptr)
{
    t_requests *request;

    request = (t_requests *)ptr;
    NL;
    printf("Coder id: %zu\n", request->coder_id);
    printf("Request id: %zu\n", request->request_id);
    printf("Last compilation: %lu\n", request->coder_last_compilation);
    NL;

}

void heappop(t_heap *heap, int (*cmp)(void *p1, void *p2), void (*del)(void *))
{
    t_heap_node *current;

    current = *heap->queue;

    if (!current)
        return ;
    while (current->left && current->right)
    {
        if (cmp(current->left->content, current->right->content))
        {
            heap_swap_node(current, current->left);
            current = current->left;
        }
        else
        {
            heap_swap_node(current, current->right);
            current = current->right;
        }
    }
    if (current->left)
    {
        heap_swap_node(current, current->left);
        current = current->left;
    }
    else if (current->right)
    {
        heap_swap_node(current, current->right);
        current = current->right;
    }
    if (current->parent && current->parent->left == current)
        current->parent->left = NULL;
    else if (current->parent && current->parent->right == current)
        current->parent->right = NULL;
    del(current->content);
    del(current);
    current = NULL;
    heap->size_queue--;
    if (heap->size_queue == 0)
        *heap->queue = NULL;
}
