#include "../include/codexion.h"

#define DISPLAY_PARAM FALSE


int main(int argc, char **argv)
{
    int params[8];
    t_sim       *sim;
    t_dongles   *dongles;
    t_coder     *coders;
    t_scheduler *scheduler;
    t_monitoring *monitoring;
    
    if(!parse_arguments(&argv[1], params))
    {
        err_msg("Error parsinfg arguments\n");
        return (1);
    }
    if (DISPLAY_PARAM)
        display_params(params, argc - 1);
    sim = sim_init(params);
    if (!sim)
        return (1);
    dongles = dongle_init(params[number_of_coders], sim);
    if (!dongles)
    {
        sim_clean(&sim);
        return (1);
    }
    coders = coders_init(params, sim, dongles);
    if (!coders)
    {
        sim_clean(&sim);
        free(dongles);
        return (1);
    }
    scheduler = scheduler_init(params, sim->queue);
    if (!scheduler)
    {
        sim_clean(&sim);
        free(dongles);
        free(coders);
        return (1);
    }
    monitoring = monitoring_init(params, sim);
    if (!monitoring)
    {
        sim_clean(&sim);
        free(dongles);
        free(coders);
        scheduler_clean(&scheduler);
        return (1);
    }
    sim_clean(&sim);
    free(dongles);
    free(coders);
    free(monitoring);
    scheduler_clean(&scheduler);
    return (0);
}
