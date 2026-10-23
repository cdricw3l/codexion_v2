/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:22:32 by cebouhad          #+#    #+#             */
/*   Updated: 2026/10/23 15:23:29 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int cmp_request_fifo(void *r1, void *r2)
{
    t_requests *request_1;
    t_requests *request_2;

    request_1 = (t_requests *)r1;
    request_2 = (t_requests *)r2;

    if (!request_1 || !request_2)
        return (FALSE);
    if (request_1->request_id < request_2->request_id)
        return (TRUE);
    return (FALSE);
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
    return (request);
}
void display_request(void *ptr)
{
    t_requests *request;

    request = (t_requests *)ptr;
    NL;
    printf("Request id:"BGRN" %zu" CRESET"\n", request->request_id);
    printf("Coder id: %zu\n", request->coder_id);
    printf("Last compilation: %lu\n", request->coder_last_compilation);
    NL;

}