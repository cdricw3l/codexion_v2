/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_coders_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:47:25 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:47:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void *check_coder_routine(void *data)
{
    t_coder *coder;
    size_t i;

    coder = (t_coder *)data;
    i = 0;

    while (i < coder->params[number_of_compiles_required])
    {
        
        pthread_mutex_lock(coder->timestamp_mu);
        (*coder->timestamp)++;
        pthread_mutex_unlock(coder->timestamp_mu);
        i++;
    }
    
}

void check_coder_thread(t_data *data)
{
    size_t i;

    i = 0;
    while (i < data->sim->params[number_of_coders])
    {
        if (pthread_create(&data->sim->thread[i], NULL, check_coder_routine, &data->coder[i]))
        {
            err_msg("Error thread_create in check_coder_thread\n");
            return ;
        }
        i++;
    }
    i = 0;
    while (i < data->sim->params[number_of_coders])
    {
        pthread_join(data->sim->thread[i], NULL);
        assert(*(data->coder[i].timestamp) = data->sim->params[number_of_compiles_required]);
        i++;
    }
}

void check_coder(int params[8], t_coder *coders, t_sim *sim, t_dongles *dongles)
{
    size_t i;

    i = 0;
    assert(coders->can_compile);
    assert(coders->can_compile_cond);
    assert(coders->can_compile_mu);
    assert(coders->dongle_left);
    assert(coders->dongle_right);
    assert(coders->queue);
    assert(coders->params[number_of_coders] == params[number_of_coders]);
    assert(coders->params[time_to_burnout] == params[time_to_burnout]);
    assert(coders->params[time_to_compile] == params[time_to_compile]);
    assert(coders->params[time_to_debug] == params[time_to_debug]);
    assert(coders->params[time_to_refactor] == params[time_to_refactor]);
    assert(coders->params[number_of_compiles_required] == params[number_of_compiles_required]);
    assert(coders->params[dongle_cooldown] == params[dongle_cooldown]);
    assert(coders->params[arbitration] == params[arbitration]);
    while (i < params[number_of_coders])
    {
        assert(*(coders[i].timestamp)==0);
        assert(coders[i].display_mu == sim->display_mu);
        assert(coders[i].coder_id == i);
        assert(coders[i].simulation_state == &sim->simulation_state);
        assert(coders[i].state_mu == sim->state_mu);
        assert(coders[i].can_compile == &sim->can_compile[i]);
        assert(coders[i].can_compile_cond == &sim->can_compile_cond[i]);
        assert(coders[i].can_compile_mu == &sim->can_compile_mu[i]);
        assert(coders[i].dongle_left == &dongles[get_dongle_id(i, params[number_of_coders], LEFT)]);
        assert(coders[i].dongle_right == &dongles[get_dongle_id(i, params[number_of_coders], RIGHT)]);
        assert(coders[i].queue == sim->queue);
        i++;
    }
    
}

void unit_coder_init(void)
{
    START_TEST;
    t_data data;
    int params[8];
    

    unit_get_param(params);
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }
    
    check_coder(params, data.coder, data.sim, data.dongles);
    check_coder_thread(&data);
    clear_data(&data, 0);
    END_TEST;
}