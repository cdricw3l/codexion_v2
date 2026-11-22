/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 21:08:11 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/20 06:50:20 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

static int arr_str_len(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
} 

static void *unit_get_arbitration_function(int arbitration)
{
	if (arbitration == FIFO)
		return(fifo);
	return(edf);
}

int unit_parsing(void)
{
    START_BLOCK;
    START_TEST;
    char *valide_arg_1[] = {"20", "500", "200", "100", "100", "10", "10", "fifo", NULL};
    char *valide_arg_2[] = {"20", "500", "200", "100", "100", "10", "10", "edf", NULL};
    int params[8];

    assert(arr_str_len(valide_arg_1) == 8);
    assert(parse_arguments(arr_str_len(valide_arg_1),valide_arg_1,params));
    assert(params[0] == 20);
    assert(params[1] == 500);
    assert(params[2] == 200);
    assert(params[3] == 100);
    assert(params[4] == 100);
    assert(params[5] == 10);
    assert(params[6] == 10);
    assert(params[7] == FIFO);
    assert(unit_get_arbitration_function(params[arbitration]) == fifo);
    assert(parse_arguments(arr_str_len(valide_arg_2),valide_arg_2,params));
    assert(params[7] == EDF);
    assert(unit_get_arbitration_function(params[arbitration]) == edf);

    char *invalide_args_0[] = {"-20", "500", "200", "100", "100", "10", "10", "fifo", NULL};
    char *invalide_args_1[] = {"20", "-500", "200", "100", "100", "10", "10", "fifo", NULL};
    char *invalide_args_2[] = {"20", "500", "dqdq", "100", "100", "10", "10", "fifo", NULL};
    char *invalide_args_3[] = {"20", "500", "200", "", "100", "10", "10", "fifo", NULL};
    char *invalide_args_4[] = {"20", "500", "200", "100", "100dwdw10", "10", "10", "fifo", NULL};
    char *invalide_args_5[] = {"20", "500", "200", "100", "100", "-20000000", "10", "fifo", NULL};
    char *invalide_args_6[] = {"20", "500", "200", "100", "100", "10", "+231221", "fifo", NULL};
    char *invalide_args_7[] = {"20", "500", "200", "100", "100", "10", "10", "hello_world", NULL};
    char *invalide_args_8[] = {"20", "500", "200", "100", "100", "10", "10", "10", NULL};
    char *invalide_args_9[] = {"500", "200", "100", "100", "10", "10", "10", NULL};
    char *invalide_args_10[] = {"20", "500", "200", "100", "100", "10", "10", "edf", NULL};

    assert(!parse_arguments(arr_str_len(invalide_args_0),invalide_args_0,params));
    assert(!parse_arguments(arr_str_len(invalide_args_1),invalide_args_1,params));
    assert(!parse_arguments(arr_str_len(invalide_args_2),invalide_args_2,params));
    assert(!parse_arguments(arr_str_len(invalide_args_3),invalide_args_3,params));
    assert(!parse_arguments(arr_str_len(invalide_args_4),invalide_args_4,params));
    assert(!parse_arguments(arr_str_len(invalide_args_5),invalide_args_5,params));
    assert(!parse_arguments(arr_str_len(invalide_args_6),invalide_args_6,params));
    assert(!parse_arguments(arr_str_len(invalide_args_7),invalide_args_7,params));
    assert(!parse_arguments(arr_str_len(invalide_args_8),invalide_args_8,params));
    assert(!parse_arguments(arr_str_len(invalide_args_9),invalide_args_9,params));
    assert(parse_arguments(arr_str_len(invalide_args_10), invalide_args_10,params));

    END_TEST;
    return(true);
}