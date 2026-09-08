/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_mutex_generation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 04:06:48 by cdric.b           #+#    #+#             */
/*   Updated: 2026/09/03 12:33:57 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int unit_mutex_generation(void)
{
    START_TEST;
    pthread_mutex_t *arr;
    int i;


    arr = init_dynamique_mutex(-10);
    assert(!arr);
    arr = init_dynamique_mutex(10);
    assert(arr);
    i = 0;
    while (i < 10)
    {
        assert(!pthread_mutex_lock(&arr[i]));
        assert(!pthread_mutex_unlock(&arr[i]));
        i++;
    }
    clean_dynamique_mutex(&arr, 10);
    assert(!arr);
    END_TEST;
    return (TRUE);
}