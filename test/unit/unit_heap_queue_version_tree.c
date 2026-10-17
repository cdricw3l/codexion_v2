/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_heap_queue_version_tree.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 11:30:18 by cdric.b           #+#    #+#             */
/*   Updated: 2026/10/17 11:28:11 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"


/*

    Fair arbitration is mandatory: when multiple coders request the same dongle,
    the dongle must grant access according to scheduler.
    With fifo, serve requests in arrival order.
    With edf, serve the coder with the earliest burnout deadline (i.e., last_compile_start
    + time_to_burnout).
*/

void display_request(t_requests *request)
{
    NL;
    printf("Node: %p\n", request);
    printf("Coder id: %zu\n", request->coder_id);
    printf("Request id: %zu\n", request->request_id);
    printf("Last compilation: %lu\n", request->coder_last_compilation);
    printf("Left: %p\n", request->left);
    printf("Right: %p\n", request->right);
    NL;

}

void display_request_queue(t_requests *tree, void (*display)(t_requests *))
{
    if(!tree)
        return ;
    display_request_queue(tree->left, display);
    display(tree);
    display_request_queue(tree->right, display);

}

void bfs_display_request_queue(t_requests *tree, void (*display)(t_requests *))
{
    t_requests **arr_requests;
    int i;

    arr_requests = get_arr_bfs(tree);
    if(!arr_requests)
    {
        printf("Error get bfs arr request");
        return ;
    }
    i = 0;
    while (arr_requests[i])
    {
        display(arr_requests[i]);
        i++;
    }
    free(arr_requests);

}

void clean_request_queue(t_requests **queue)
{
    while (*queue)
    {
        free(*queue);
        queue++;
    }
}

t_requests *create_request(int request_id, int coder_id, clock_t last_compilation)
{
    t_requests *request;

    request = malloc(sizeof(t_requests));
    if (!request)
    {
        perror("Error creation request:");
        return (NULL);
    }
    request->coder_id = coder_id;
    request->request_id = request_id;
    request->coder_last_compilation = last_compilation;
    request->left = NULL;
    request->right = NULL;
    return (request);
}


// int heapfy(t_requests **arr_requests, int queue_size, int mode)
// {

//     int i;

//     i = 0;
//     while (arr_requests[i])
//     {
//         display_request(arr_requests[i++]);
//     }
    
    
// }

int save_request(t_dongle *dongle, t_requests *request_node)
{
    t_requests **requests_arr;
    t_requests *node;

    if (*dongle->requests_queue == NULL)
    {
        *dongle->requests_queue = request_node;
        dongle->request_queue_size++;
        printf("Add root request\n");
        return (TRUE);
    }
    requests_arr = get_arr_bfs(*dongle->requests_queue);
    if(!requests_arr)
    {
        printf("Error creation requests arr\n");
        return (FALSE);
    }
    node = requests_arr[(dongle->request_queue_size - 1) / 2];
    if(node->left == NULL)
    {
        printf("Add node to the left\n");
        node->left = request_node;
    }
    else if (node->right == NULL)
    {
        printf("Add node to the right\n");
        node->right = request_node;
    }
    dongle->request_queue_size++;
    return (TRUE);
}

int unit_heap_queue_fifo(void)
{
    
    t_requests **queue;
    t_dongle dongle_1;
    t_requests *request;
    int i;
    int number_of_request;
   
    queue = malloc(sizeof(t_requests *));
    if (!queue)
        return(FALSE);
    *queue = NULL;
    dongle_1.requests_queue = queue;
    if( pthread_mutex_init(&dongle_1.dongle, NULL))
    {
        perror("Mutex initialisation error:");
        free(queue);
        return (FALSE);
    }
    dongle_1.last_use = 0;
    dongle_1.request_queue_size = 0;
    
    i = 1;
    number_of_request = 11;
    while (i <= number_of_request)
    {
        request = create_request(i, 0, 0);
        save_request(&dongle_1, request);
        i++;
    }
    request = create_request(0,0,0);
    save_request(&dongle_1, request);
    bfs_display_request_queue(*dongle_1.requests_queue, display_request);
    clean_request_queue(queue);
    free (queue);
    return(TRUE);
}