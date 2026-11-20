#ifndef UNIT_H
#define UNIT_H

#include "../include/test.h"



int     unit_request(void);
int     unit_parsing(void);
int     unit_utils(void);
int     unit_heap(void);
int     unit_initialisation(void);
int     unit_monitoring(void);
void    unit_scheduler(void);

/* unit utils */
char	*ft_itoa(int n);
void    unit_get_param(int params[8]);



#endif
