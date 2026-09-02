/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 21:08:11 by cdric.b           #+#    #+#             */
/*   Updated: 2026/09/02 02:51:30 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit.h"

int test_unit_parsing(void)
{
    START_TEST;
    char *valide_arg_1[] = {"20", "500", "200", "100", "100", "10", "10", "fifo", NULL};
    char *valide_arg_2[] = {"20", "500", "200", "100", "100", "10", "10", "edf", NULL};
    int params[8];

    assert(parse_arguments(valide_arg_1,params));
    assert(params[0] == 20);
    assert(params[1] == 500);
    assert(params[2] == 200);
    assert(params[3] == 100);
    assert(params[4] == 100);
    assert(params[5] == 10);
    assert(params[6] == 10);
    assert(params[7] == FIFO);
    assert(parse_arguments(valide_arg_2,params));
    assert(params[7] == EDF);

    char *invalide_args_0[] = {"-20", "500", "200", "100", "100", "10", "10", "fifo", NULL};
    char *invalide_args_1[] = {"20", "-500", "200", "100", "100", "10", "10", "fifo", NULL};
    char *invalide_args_2[] = {"20", "500", "dqdq", "100", "100", "10", "10", "fifo", NULL};
    char *invalide_args_3[] = {"20", "500", "200", "", "100", "10", "10", "fifo", NULL};
    char *invalide_args_4[] = {"20", "500", "200", "100", "100dwdw10", "10", "10", "fifo", NULL};
    char *invalide_args_5[] = {"20", "500", "200", "100", "100", "-20000000", "10", "fifo", NULL};
    char *invalide_args_6[] = {"20", "500", "200", "100", "100", "10", "+231221", "fifo", NULL};
    char *invalide_args_7[] = {"20", "500", "200", "100", "100", "10", "10", "hello_world", NULL};
    char *invalide_args_8[] = {"20", "500", "200", "100", "100", "10", "10", "10", NULL};
    char *invalide_args_9[] = {"20", "500", "200", "100", "100", "10", "10", "edf", NULL};

    assert(!parse_arguments(invalide_args_0,params));
    assert(!parse_arguments(invalide_args_1,params));
    assert(!parse_arguments(invalide_args_2,params));
    assert(!parse_arguments(invalide_args_3,params));
    assert(!parse_arguments(invalide_args_4,params));
    assert(!parse_arguments(invalide_args_5,params));
    assert(!parse_arguments(invalide_args_6,params));
    assert(!parse_arguments(invalide_args_7,params));
    assert(!parse_arguments(invalide_args_8,params));
    assert(parse_arguments(invalide_args_9,params));

    END_TEST;
    return(TRUE);
}