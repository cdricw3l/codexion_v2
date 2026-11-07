#include "../include/test.h"

int main(void)
{
    START_TEST;
    t_sim *sim;
    int params[8];  

    params[number_of_coders] = 8;
    sim = sim_init(params);
    printf(BGRN"INITIALISATION OK"CRESET"\n");
    clean_sim(&sim);
    return (0);
}