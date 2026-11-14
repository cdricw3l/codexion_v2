#include "../include/test.h"


void unit_get_param(int params[8])
{
    params[number_of_coders] = NB_CODER;
    params[time_to_burnout] = 500;
    params[time_to_compile] = 200;
    params[time_to_debug] = 100;
    params[time_to_refactor] = 100;
    params[number_of_compiles_required] = 20;
    params[dongle_cooldown] = 10;
    params[scheduler] = FIFO;
}

int main(void)
{
    START_TEST;

    t_coder *coder;
    int params[8];
    size_t i;

    unit_get_param(params); 
    coder = malloc(sizeof(t_coder));
    if (!coder)
        return (1);
    coder->display_mu = init_dynamique_mutex(1);
    coder->simulation_start = get_now();
    coder->coder_id = 1;
    i = 0;
    while (i < 10)
    {
        display_action(coder,TAKE);
        display_action(coder,COMPILE);
        usleep(params[time_to_compile] * 1000);
        display_action(coder,DEBUG);
        usleep(params[time_to_debug] * 1000);
        display_action(coder,REFACTO);
        usleep(params[time_to_refactor] * 1000);
        i++;
    }
    display_action(coder,END);
    
    return (0);
}