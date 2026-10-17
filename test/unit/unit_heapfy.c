/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heapfy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/17 18:35:18 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <string.h>



void print_str(void *content)
{
    char *str;

    str = (char *)content;
    printf("content: %s\n", str);
}

void print_node(t_heap_node *node)
{

    if (!node)
        return ;
    NL;
    printf("Node: %p\n", node);
    print_str(node->content);
    printf("Parent: %p\n", node->parent);
    printf("Left: %p\n", node->left);
    printf("Right: %p\n", node->right);
    NL;

}

void heap_iter(t_heap_node *root, void (f)(t_heap_node *node))
{
    if (!root)
        return;
    heap_iter(root->left, f);
    f(root);
    heap_iter(root->right, f);
}






void print_bit(int value, int bit)
{
    int size;

    size = bit -1;
    while (size >= 0)
    {
        printf("%d", value >> size & 1);
        size--;
    }
    NL;
}

int manual_heapfy(void)
{
    t_heap_node *node_1;
    t_heap_node *node_2;
    t_heap_node *node_3;
    t_heap_node *node_4;
    t_heap_node *node_5;
    t_heap_node *node_6;
    t_heap_node *node_7;
    t_heap_node *node_8;
    t_heap_node *node_9;
    t_heap_node *node_10;
    t_heap_node *node_11;
    t_heap_node *node_12;
    t_heap_node **queue;
    size_t         heap_size;

    queue = malloc(sizeof(t_heap_node *));
    if (!queue)
    {
        perror("Error initialisation queue: ");
        return (FALSE);
    }

    node_1 = heap_new_node(strdup("1"));
    node_2 = heap_new_node(strdup("2"));
    node_3 = heap_new_node(strdup("3"));
    node_4 = heap_new_node(strdup("4"));
    node_5 = heap_new_node(strdup("5"));
    node_6 = heap_new_node(strdup("6"));
    node_7 = heap_new_node(strdup("7"));
    node_8 = heap_new_node(strdup("8"));
    node_9 = heap_new_node(strdup("9"));
    node_10 = heap_new_node(strdup("10"));
    node_11 = heap_new_node(strdup("11"));
    node_12 = heap_new_node(strdup("12"));
    
    node_1->left = node_2;
    node_1->right = node_3;

    node_2->left = node_4;
    node_2->right = node_5;
    
    node_3->left = node_6;
    node_3->right = node_7;

    node_4->left = node_8;
    node_4->right = node_9;

    node_5->left = node_10;
    node_5->right = node_11;

    heap_size = 11;
    *queue = node_1;
    
    heap_add_node(queue, node_12, &heap_size);

    //heap_iter(*queue, print_node);
    assert(heap_size == 12);
    return (TRUE);
}

int auto_heapfy(void)
{
    t_heap_node **queue;
    t_heap_node *node;
    size_t      heap_size;
    int         i;

    queue = malloc(sizeof(t_heap_node *));
    if (!queue)
    {
        perror("Error initialisation queue: ");
        return (FALSE);
    }
    i = 1;
    heap_size = 0;
    *queue = NULL;
    while (i <= 12)
    {
        node = heap_new_node(ft_itoa(i));
        printf("voici i %d\n", i);
        assert(heap_add_node(queue, node, &heap_size) == TRUE);
        i++;
    }
    heap_iter(*queue, print_node);
    heap_clear(*queue, free);
    free(queue);
    return (TRUE);
}

int unit_heapfy(void)
{
    auto_heapfy();
    return (TRUE);
}