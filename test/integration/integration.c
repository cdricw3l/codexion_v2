#include "integration.h"


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
    t_sim       *sim;
    t_dongles   *dongles;
    t_coder     *coders;
    t_scheduler *scheduler;
    t_monitoring *monitoring;
    
    int params[8];

    unit_get_param(params);
    sim = sim_init(params);
    if (!sim)
        return (1);
    dongles = dongle_init(params[number_of_coders], sim);
    if (!dongles)
    {
        clean_sim(&sim);
        return (1);
    }
    coders = coders_init(sim, dongles, params);
    if (!coders)
    {
        clean_sim(&sim);
        free(dongles);
        return (1);
    }
    scheduler = scheduler_init(params, sim);
    if (!scheduler)
    {
        clean_sim(&sim);
        free(dongles);
        free(coders);
        return (1);
    }
    monitoring = monitoring_init(params, sim);
    if (!monitoring)
    {
        clean_sim(&sim);
        free(dongles);
        free(coders);
        clean_scheduler(&scheduler);
        return (1);
    }
    assert(sim);
    assert(dongles);
    assert(coders);
    assert(scheduler);
    assert(monitoring);

    
    
    
    start_coder_thread(sim, coders, scheduler);

    clean_sim(&sim);
    free(dongles);
    free(coders);
    free(monitoring);
    clean_scheduler(&scheduler);

    return (0);
}