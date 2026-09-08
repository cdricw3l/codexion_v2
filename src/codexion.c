#include "../include/codexion.h"

#define DISPLAY_PARAM TRUE

int main(int argc, char **argv)
{
    int params[8];


    
    if(!parse_arguments(&argv[1], params))
        return (write(STDERR_FILENO, "Error parsinfg arguments\n", strlen("Error parsinfg arguments\n")));
    if (DISPLAY_PARAM)
        display_params(params, argc - 1);
    
    return (0);
}