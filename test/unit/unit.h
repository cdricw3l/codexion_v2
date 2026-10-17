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



int unit_heap_queue_fifo(void);
int unit_heapfy(void);

/* utils */
char	*ft_itoa(int n);
#endif
