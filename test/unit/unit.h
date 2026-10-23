#ifndef UNIT_H
#define UNIT_H

#include "../0_include/test.h"
#include "../../include/codexion.h"
#include "../../src/heap/heap.h"


int unit_parsing(void);
int unit_mutex_generation(void);
int unit_cond_generation(void);


/* bfs */
int unit_bfs_algo(void);
t_requests **get_arr_bfs(t_requests *tree);
t_requests *create_request(int request_id, int coder_id, clock_t last_compilation);
void display_request(void *ptr);

int unit_heap_queue_fifo(void);
int unit_heap(void);

/* utils */
char	*ft_itoa(int n);
#endif
