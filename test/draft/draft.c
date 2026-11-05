#include "../include/test.h"

int main(void)
{
    bool can_compile;
    bool *can;

    can_compile = true;
    can = &can_compile;

    assert(*can == true);

    printf("voici l'adresse %p\n", &can_compile);
    printf("voici l'adresse %p\n", can);
    return (0);
}