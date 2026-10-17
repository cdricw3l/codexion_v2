/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heapfy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:35:27 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/17 16:10:23 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"
#include <string.h>

typedef struct s_heap_node
{
    void *content;

    struct s_heap_node *left;
    struct s_heap_node *right;

} t_heap_node;

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
    printf("Left: %p\n", node->left);
    printf("Left: %p\n", node->right);
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

t_heap_node *new_node(void *content)
{
    t_heap_node *node;

    node = malloc(sizeof(t_heap_node));
    if (!node)
    {
        perror("Node allocation error:");
        return (NULL);
    }
    node->content = content;
    node->left = node->right = NULL;
    return (node);
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

void get_path(int value, char buffer[17])
{
    int bit;
    int on;
    int i;

    bit = 15;
    on = 0;
    i = 0;
    while (bit >= 0)
    {
        if (!on && ((value >> bit) & 1) == 1)
        {
            on = 1;
            bit--;
            continue;
        }
        if (on)
            buffer[i++] = ((value >> bit) & 1) + '0';
        bit--;
    }
    buffer[i] = '\0';
}

int ft_heap_add(t_heap_node **heap, t_heap_node *node, int *heap_size)
{
    int         target_node;
    int         i;
    char        buffer[17];
    t_heap_node *current_node;

    if (!heap || !node || (*heap_size) < 0)
        return(FALSE) ;
    if(!*heap)
    {
        *heap = node;
        (*heap_size)++;
        return(TRUE) ;
    }
    target_node = (*heap_size + 1) / 2;
    get_path(target_node, buffer);
    current_node = *heap;
    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '1')
            current_node = current_node->right;
        else if (buffer[i] == '0')
            current_node = current_node->left;
        i++;
    }
    if((*heap_size + 1) % 2 == 0)
    {
        if (current_node->left)
            return(FALSE);
        current_node->left = node;
    }
    else 
    {
        if (current_node->right)
            return(FALSE);
        current_node->right = node;
    }
    (*heap_size)++;
    return (TRUE);
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
    int         heap_size;

    queue = malloc(sizeof(t_heap_node *));
    if (!queue)
    {
        perror("Error initialisation queue: ");
        return (FALSE);
    }

    node_1 = new_node(strdup("1"));
    node_2 = new_node(strdup("2"));
    node_3 = new_node(strdup("3"));
    node_4 = new_node(strdup("4"));
    node_5 = new_node(strdup("5"));
    node_6 = new_node(strdup("6"));
    node_7 = new_node(strdup("7"));
    node_8 = new_node(strdup("8"));
    node_9 = new_node(strdup("9"));
    node_10 = new_node(strdup("10"));
    node_11 = new_node(strdup("11"));
    node_12 = new_node(strdup("12"));
    
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
    
    ft_heap_add(queue, node_12, &heap_size);

    //heap_iter(*queue, print_node);
    assert(heap_size == 12);
    return (TRUE);
}

int auto_heapfy(void)
{
    t_heap_node **queue;
    t_heap_node *node;
    int         heap_size;
    int         i;

    queue = malloc(sizeof(t_heap_node *));
    if (!queue)
    {
        perror("Error initialisation queue: ");
        return (FALSE);
    }
    i = 0;
    heap_size = 0;
    while (i < 12)
    {
        node = new_node(ft_itoa(i));
        printf("voici i %d\n", i);
        assert(ft_heap_add(queue, node, &heap_size) == TRUE);
        i++;
    }
    
    return (TRUE);
}

int unit_heapfy(void)
{
    auto_heapfy();
    return (TRUE);
}