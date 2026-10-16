/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_bfs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 18:08:02 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/16 13:03:33 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"




void get_tree_size(t_requests *tree, int *i)
{
    if(tree)
        (*i)++;
    if(!tree)
        return ;
    get_tree_size(tree->left, i);
    get_tree_size(tree->right, i);

}

void display_queue(t_requests **queue)
{
    int i;

    i = 0;
    while (queue[i])
    {
        printf("request id %zu \n", queue[i]->request_id);
        i++;
    }
    
}

int is_queue_empty(t_requests **queue)
{
    if(!queue || !(*queue))
        return (TRUE);
    return (FALSE);
}

void push(t_requests **queue, t_requests *request)
{
    int i;

    i = 0;
    if (!queue)
        return ;
    while (queue[i])
        i++;
    queue[i] = request;    
}

void pop(t_requests **queue)
{
    int i;

    if (!queue || !(*queue))
        return ;
    i = 1;
    while (queue[i])
    {
        queue[i - 1] = queue[i];
        i++;    
    }
    queue[i - 1] = NULL;
}

t_requests **get_arr_bfs(t_requests *tree)
{
    int size;
    t_requests **queue;
    t_requests **arr;
    t_requests *tmp;
    
    size = 0;
    get_tree_size(tree, &size);
    if (size == 0)
        return (NULL);
    queue = malloc(sizeof(t_requests *) * size);
    if (!queue)
        return (NULL);
    arr = malloc(sizeof(t_requests *) * (size + 1));
    if (!arr)
    {
        free(queue);
        return (NULL);
    }
    memset(queue, 0, sizeof(t_requests *) * size);
    memset(arr, 0, sizeof(t_requests *) * (size+1));
    push(queue, tree);
    while (!is_queue_empty(queue))
    {
        tmp = queue[0];
        push(arr, tmp);
        pop(queue);
        push(queue, tmp->left);
        push(queue, tmp->right);
    }
    free(queue);
    push(arr, NULL);
    assert(arr);
    return (arr);
}

int unit_bfs_algo(void)
{

    t_requests r0;
    t_requests r1;
    t_requests r2;
    t_requests r3;
    t_requests r4;
    t_requests r5;
    t_requests r6;
    t_requests r7;
    t_requests r8;
    t_requests r9;
    t_requests r10;
    
    r0.request_id = 0;
    r1.request_id = 1;
    r2.request_id = 2;
    r3.request_id = 3;
    r4.request_id = 4;
    r5.request_id = 5;
    r6.request_id = 6;
    r7.request_id = 7;
    r8.request_id = 8;
    r9.request_id = 9;
    r10.request_id = 10;

    r0.left = &r1;
    r0.right = &r2;

    r1.left = &r3;
    r1.right = &r4;

    r2.left = &r5;
    r2.right = &r6;

    r3.left = &r7;
    r3.right = &r8;
    r4.left = &r9;
    r4.right = &r10;
    r5.left = NULL;
    r5.right = NULL;
    r6.left = NULL;
    r6.right = NULL;
    r7.left = NULL;
    r7.right = NULL;
    r8.left = NULL;
    r8.right = NULL;
    r9.left = NULL;
    r9.right = NULL;
    r10.left = NULL;
    r10.right = NULL;
    

    

    t_requests **arr = get_arr_bfs(&r0);
    assert(arr);
    assert(*arr);
    assert(arr[0]->request_id == 0);
    assert(arr[1]->request_id == 1);
    assert(arr[2]->request_id == 2);
    assert(arr[3]->request_id == 3);
    assert(arr[4]->request_id == 4);
    assert(arr[5]->request_id == 5);
    assert(arr[6]->request_id == 6);
    assert(arr[7]->request_id == 7);
    assert(arr[8]->request_id == 8);
    assert(arr[9]->request_id == 9);
    assert(arr[10]->request_id == 10);
    free(arr);
    return (TRUE);
}