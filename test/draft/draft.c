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
    t_data  data;
    int     params[8];

    unit_get_param(params);
    
    display_params(data.sim->params, data.sim->params[number_of_coders]);
    return (0);
}