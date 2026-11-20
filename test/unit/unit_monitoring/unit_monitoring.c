// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unit_monitoring.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/11/11 20:25:01 by cebouhad          #+#    #+#             */
// /*   Updated: 2026/11/19 20:13:46 by cebouhad         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "unit_monitoring.h"

// static void	unit_action(t_coder *coder, int action)
// {
// 	if (action == COMPILE)
// 	{
// 		usleep(coder->params[time_to_compile] * 1000);
// 		set_timestamp(coder);
// 	}
// 	if (action == DEBUG)
// 		usleep(coder->params[time_to_debug] * 1000);
// 	if (action == REFACTO)
// 		usleep(coder->params[time_to_refactor] * 1000);
// }

// int check_timestamp(t_monitoring *monitor, size_t coder_id)
// {
//     uint64_t now;
//     uint64_t elapsed;

//     now = get_now();

//     elapsed = (now - get_timestamp(&monitor->timestamp[coder_id], &monitor->timestamp_mu[coder_id])) / 1000000;
//     //printf("start: %ld end: %ld\n", now, get_timestamp(&monitor->timestamp[coder_id], &monitor->timestamp_mu[coder_id]));
//     //printf("coder id: %ld elapsed: %ld\n", coder_id, elapsed);
//     if (elapsed > monitor->params[time_to_burnout])
//     {
//         return (FALSE);
//     }
//     return(TRUE);
// }

// void *monitoring_thread(void *data)
// {
//     t_monitoring *monitoring;
//     size_t i;
//     monitoring = (t_monitoring *)data;

//     while (get_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu))
//     {
//         i = 0;
//         while (i < monitoring->params[number_of_coders])
//         {
//             if (!check_timestamp(monitoring, i))
//             {
//                 display_action(&monitoring->coders[i], 4);
//                 set_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu, OFF);
//                 return (NULL);
//             }
//             i++;
//         }
//     }
// }

// void *unit_scheduler_routine(void *data)
// {
//     t_scheduler *scheduler;
//     t_request *request;
    
//     scheduler = (t_scheduler *)data;
//     while (get_sim_state(scheduler->simulation_state, scheduler->simulation_state_mu))
//     {
        
//     }
    
// }

// void *unit_coder_monitor_routine(void *data)
// {
//     t_coder *coder;
//     t_request *request;
//     size_t  i;

//     coder = (t_coder *)data;
//     i = 0;

//     while (get_sim_state(coder->simulation_state, coder->simulation_state_mu) && coder->params[number_of_compiles_required] > i)
//     {
//         assert(request_push(coder));
//         pthread_mutex_lock(coder->can_compile_mu);
//         while (*coder->can_compile == FALSE)
//         {
//             pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
//         }
        
//         assert(!pthread_mutex_lock(coder->dongle_right->dongle));
//         assert(!pthread_mutex_lock(coder->dongle_left->dongle));
//         display_action(coder, COMPILE);
//         unit_action(coder, COMPILE);
//         assert(!pthread_mutex_unlock(coder->dongle_right->dongle));
//         assert(!pthread_mutex_unlock(coder->dongle_left->dongle));
//         *coder->can_compile == FALSE;
//         pthread_mutex_unlock(coder->can_compile_mu);
//         display_action(coder, DEBUG);
//         unit_action(coder, DEBUG);
//         display_action(coder, REFACTO);
//         unit_action(coder, REFACTO);
//         i++;
//     }
//     assert(i == coder->params[number_of_compiles_required]);
//     return (NULL);
// }

// static void unit_monitoring_thread(t_sim *sim, t_coder *coder, t_monitoring *monitor)
// {
//     START_TEST;
//     uint64_t start;
//     pthread_t monitor_thread;

//     set_sim_state(&sim->simulation_state, sim->simulation_state_mu, ON);
//     start = get_now();
//     assert(launch_coders(sim, coder, unit_coder_monitor_routine, start));
//     assert(!pthread_create(&monitor_thread, NULL, monitoring_thread, monitor));
//     assert(joint_coders(sim));
//     set_sim_state(&sim->simulation_state, sim->simulation_state_mu, OFF);
//     pthread_join(monitor_thread, NULL);
//     END_TEST;
// }

// void unit_check_timestamp(t_coder *coders, t_monitoring *monitoring)
// {
//     t_coder *coder;

//     coder = &coders[0];
// }

// int unit_monitoring(void)
// {
//     START_BLOCK;
//     t_sim *sim;
//     t_dongles *dongle;
//     t_coder *coders;
//     t_scheduler *scheduler;
//     t_monitoring *monitor;

//     int param[8];
//     unit_get_param(param);
//     display_params(param, param[number_of_coders]);

//     //assert(param[time_to_burnout] < param[time_to_refactor]+param[time_to_compile]+param[time_to_debug]);
//     sim = sim_init(param);
//     assert(sim);
//     dongle = dongle_init(param, sim);
//     assert(dongle);
//     coders = coders_init(param, sim, dongle);
//     assert(coders);
//     scheduler = scheduler_init(param, sim);
//     assert(scheduler);
//     monitor = monitoring_init(param, sim, coders);
//     assert(monitor);
//     // set_timestamp(&coders[0]);
//     // usleep(param[time_to_compile] * 1000);
//     // assert(check_timestamp(monitor,0));

    
//     unit_monitoring_thread(sim, coders, monitor);
//     free(monitor);
//     free(coders);
//     free(dongle);
//     clean_scheduler(&scheduler);
//     clean_sim(&sim);

//     return (TRUE);

// }

